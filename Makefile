TARGET_MODULE := test
obj-m :=$(TARGET_MODULE).o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm -rf *.o *.ko *.mod.* *.symvers *.order *.mod.cmd *.mod
	$(RM) client out

load:
	sudo insmod $(TARGET_MODULE).ko

unload:
	sudo rmmod $(TARGET_MODULE) || true >/dev/null

client_c:
	gcc client.c -o client

client_do:
	sudo ./client

client:
	$(MAKE) client_c
	$(MAKE) client_do