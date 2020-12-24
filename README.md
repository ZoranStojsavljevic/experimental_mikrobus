### Newest Mikrobus (branch mikrobusv3) driver release

The patch is added to the BB-kernel 5.8.18-bone24 release

The kernel used is the following: 5.18.8-bone24

https://github.com/RobertCNelson/bb-kernel

Execute the following to build the custom menuconfig:

	host$ git clone https://github.com/RobertCNelson/bb-kernel.git
	host$ cd bb-kernel
	host$ git remote show origin
	host$ git checkout am33x-v5.8
	host$ ./build_kernel.sh

For the latest bb-kernel: 5.18.8-bone24

### MikroBUS version3 (branch mikrobusv3) Out Of the kernel Tree setup

IMPORTANT: For MIKROBUS driver Out Of Tree the following should be set in .config:

	CONFIG_MIKROBUS=m
	CONFIG_W1=m
	CONFIG_W1_MASTER_GPIO=m

The following is the modules dynamic dependency loading order:

	w1-gpio -> mikrobus -> mikrobus_id

After that, the following is the loadable modules traces:

	debian@arm:~$ lsmod
	Module                  Size  Used by
	spidev                 20480  0
	evdev                  20480  1
	usb_f_acm              20480  2
	u_serial               24576  3 usb_f_acm
	usb_f_ncm              24576  2
	usb_f_rndis            24576  4
	u_ether                24576  2 usb_f_ncm,usb_f_rndis
	libcomposite           49152  16 usb_f_acm,usb_f_ncm,usb_f_rndis
	iptable_nat            16384  0
	nf_nat                 28672  1 iptable_nat
	nf_conntrack           98304  1 nf_nat
	nf_defrag_ipv6         20480  1 nf_conntrack
	nf_defrag_ipv4         16384  1 nf_conntrack
	iptable_mangle         16384  0
	iptable_filter         16384  0
	-------
	mikrobus_id            16384  0
	mikrobus               20480  1 mikrobus_id
	w1_gpio                16384  0
	wire                   32768  3 mikrobus_id,w1_gpio,mikrobus
	-------
	ip_tables              24576  3 iptable_mangle,iptable_filter,iptable_nat
	x_tables               24576  3 iptable_mangle,ip_tables,iptable_filter

### Miscellaneous topic

	$ ls -al /lib/modules/$(uname -r)/kernel/drivers/misc/mikrobus
	$ sudo rm /lib/modules/$(uname -r)/kernel/drivers/misc/mikrobus/*
	$ sudo cp mikrobus.ko /lib/modules/$(uname -r)/kernel/drivers/misc/mikrobus
	$ sudo cp mikrobus_id.ko /lib/modules/$(uname -r)/kernel/drivers/misc/mikrobus

