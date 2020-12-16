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

### IMPORTANT: For MIKROBUS driver Out Of Tree the following should be set in .config:

	CONFIG_MIKROBUS=m
	CONFIG_W1=m
	CONFIG_W1_MASTER_GPIO=m

In order to be able to test Mikrobus (mikrobusv3) Driver out-of-kernel-tree.
