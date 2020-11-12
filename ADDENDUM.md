### Newest Mikrobus driver release

This driver comes from the following patch:

https://github.com/RobertCNelson/bb-kernel/commit/1b0087eb82e110b24893c83959ab375ed8b3f44b

The patch is added to the BB-kernel 5.8.16-bone19 release

The kernel used is the following: 5.18.8-bone23

https://github.com/RobertCNelson/bb-kernel

Execute the following to build the custom menuconfig:

	host$ git clone https://github.com/RobertCNelson/bb-kernel.git
	host$ cd bb-kernel
	host$ git remote show origin
	host$ git checkout am33x-v5.8
	host$ ./build_kernel.sh

For the latest bb-kernel: 5.18.8-bone23
