TARGET_MODULE := test
obj-m :=$(TARGET_MODULE).o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	gcc client.c -o client

clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order *.mod.cmd *.mod
	$(RM) client out

load:
	sudo insmod $(TARGET_MODULE).ko

unload:
	sudo rmmod $(TARGET_MODULE) || true >/dev/null

plot:
	gnuplot plot.gp

check: all
	$(MAKE) unload
	$(MAKE) load
	sudo ./client
	$(MAKE) unload