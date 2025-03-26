ifneq ($(KERNELRELEASE),)
	obj-m := Cust_Module.o
else

KERNELDIR ?= /lib/modules/$(shell uname)/Build

PWD := $(shell pwd)

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif

clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean