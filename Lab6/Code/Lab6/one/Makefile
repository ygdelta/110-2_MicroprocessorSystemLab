obj-m := hellod.o 
kernel_DIR = /usr/src/linux-headers-4.9.201-tegra-ubuntu18.04_aarch64/kernel-4.9/ #有可能需要更改位址

PWD := $(shell pwd)
all:
	make -C $(kernel_DIR) SUBDIRS=$(PWD)
clean:
	rm *.o *.ko *mod.C
.PHONY:
	clean