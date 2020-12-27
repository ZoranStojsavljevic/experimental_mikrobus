mikrobus-y :=	mikrobus_core.o	mikrobus_manifest.o mikrobus_info.o
obj-$(CONFIG_MIKROBUS) += mikrobus.o

KDIR ?= /lib/modules/`uname -r`/build

all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	make -C $(KDIR) M=$(PWD) clean
install:
	sudo cp *.ko /lib/modules/$(shell uname -r)/kernel/drivers/misc/mikrobus
	sudo depmod -a
