#include <linux/module.h>
#include <linux/init.h>
#include <linux/sort.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/cdev.h>

MODULE_LICENSE("Dual BSD/GPL");

#define DEV_NAME "sort_test"
#define LEN 10000

static int cmpint(const void *a, const void *b)
{
    return *(int *) a - *(int *) b; 
}


static dev_t sort_dev = 0;
static struct cdev *sort_cdev;
static struct class *sort_class;
static ktime_t kt;
static ssize_t sort_read(struct file *filp,
                         char *buf,
                         size_t size,
                         loff_t *f_pos)
{
    int *a = kmalloc(sizeof(int) * LEN, GFP_KERNEL);
    int r = 1;
    for(int i = 0; i < LEN; i++) {
        r = (r * 725861) % 6599;
        a[i] = r;
    }
    kt = ktime_get();
    sort(a, LEN, sizeof(int), cmpint, NULL);
    kt = ktime_sub(ktime_get(), kt);
    return ktime_to_us(kt);
}

const struct file_operations sort_fops = {
    .read = sort_read
};

static int sort_init(void)
{
    int rc = 0;


    // Let's register the device
    // This will dynamically allocate the major number
    rc = alloc_chrdev_region(&sort_dev, 0, 1, DEV_NAME);

    if (rc < 0) {
        printk(KERN_ALERT
               "Failed to register the fibonacci char device. rc = %i",
               rc);
        return rc;
    }

    sort_cdev = cdev_alloc();
    if (sort_cdev == NULL) {
        printk(KERN_ALERT "Failed to alloc cdev");
        rc = -1;
        goto failed_cdev;
    }
    sort_cdev->ops = &sort_fops;
    rc = cdev_add(sort_cdev, sort_dev, 1);

    if (rc < 0) {
        printk(KERN_ALERT "Failed to add cdev");
        rc = -2;
        goto failed_cdev;
    }

    sort_class = class_create(THIS_MODULE, DEV_NAME);

    if (!sort_class) {
        printk(KERN_ALERT "Failed to create device class");
        rc = -3;
        goto failed_class_create;
    }

    if (!device_create(sort_class, NULL, sort_dev, NULL, DEV_NAME)) {
        printk(KERN_ALERT "Failed to create device");
        rc = -4;
        goto failed_device_create;
    }
    return rc;
failed_device_create:
    class_destroy(sort_class);
failed_class_create:
    cdev_del(sort_cdev);
failed_cdev:
    unregister_chrdev_region(sort_dev, 1);
    return rc;
}

static void sort_exit(void)
{
    device_destroy(sort_class, sort_dev);
    class_destroy(sort_class);
    cdev_del(sort_cdev);
    unregister_chrdev_region(sort_dev, 1);
}

module_init(sort_init);
module_exit(sort_exit);
