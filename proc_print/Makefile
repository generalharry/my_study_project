KERNELDIR=/usr/src/linux-headers-4.2.0-34-generic
PWD:=$(shell pwd)
INSTALLDIR=$(PWD)
CC=gcc

$(warning >>> harry debug build list module)
obj-m := proc_print.o test.o


print:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

clean:
	rm -rf .*.cmd .tmp_versions *.o *.ko *.mod.c *.markers *.order *.symvers
.PHONY:modules clean
