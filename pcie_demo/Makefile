obj-m := hello_pcie.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

PWD := $(shell pwd)

ccflags-y += -g

all:
	make -C $(KERNELDIR) SUBDIRS=$(PWD) modules

clean:
	make -C $(KERNELDIR) SUBDIRS=$(PWD) clean
