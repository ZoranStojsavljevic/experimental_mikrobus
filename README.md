## MikroBUS (mikrobusv2 branch)

MikroBUS kernel driver for instantiating mikroElektronika Click Boards from Manifest descriptors, See [eLinux/mikrobus](https://elinux.org/mikrobus) for more information.

### Trying out:

	git clone https://github.com/ZoranStojsavljevic/mikrobus.git
	cd mikrobus
	make all
	sudo insmod mikrobus.ko

### Status

* Basic Clicks and Clicks with IRQ Requirement working
* Debug Interfaces for adding and Removing mikroBUS ports
* Multiple Devices on a Click (in single manifest)
* Manifest Parsing Logic complete
* Fetching Manifest from EEPROM

### TODO

* Devices under an i2c-gate
* Devices with gpio_cs

### Attaching PocketBeagle MikroBUS port 1 (Techlab mikroBUS port)(run as root)

	printf "%b" '\x01\x00\x00\x59\x32\x17' > /sys/bus/mikrobus/add_port

The bytes in the byte array sequence are (in order):

* i2c_adap_nr
* spi_master_nr
* serdev_ctlr_nr
* rst_gpio_nr
* pwm_gpio_nr
* int_gpio_nr

Note:- Attaching the mikrobus driver automatically probes an EEPROM on the I2C bus and if the probe is succesful, the driver tries to load a manifest from the eeprom and instantiate the click devices on the mikrobus port.

### Instantiating a Click Device through a manifest blob

See [manifesto tool](https://github.com/vaishnav98/manifesto/tree/mikrobus) for creating manifest blobs and instantiating clicks on the mikrobus port.

### Newest MikroBUS driver release (mikrobusv2 branch)

This driver comes from the following patch:

https://github.com/RobertCNelson/bb-kernel/commit/1b0087eb82e110b24893c83959ab375ed8b3f44b

The patch is added to the BB-kernel 5.8.16-bone19 release

The kernel must be at least the same version, or later.

https://github.com/RobertCNelson/bb-kernel

Execute the following to build the custom menuconfig:

	$ git clone https://github.com/RobertCNelson/bb-kernel.git
	$ cd bb-kernel
	$ git remote show origin
	$ git checkout am33x-v5.10
	$ git branch
	$ ./build_kernel.sh

For the latest 5.10.x bb-kernel.

### IMPORTANT - WARNING: While building the kernel CONFIG_MIKROBUS option MUST be set to <m>!

	$ cat .config | grep MIKROBUS
	CONFIG_MIKROBUS=m

In order to be able to test Mikrobus Driver out-of-kernel-tree.

### Location of modules in the rootfs to be loaded automatically

	$ ls -al /lib/modules/$(uname -r)/kernel/drivers/misc/mikrobus
	$ sudo cp mikrobus.ko /lib/modules/$(uname -r)/kernel/drivers/misc/mikrobus
