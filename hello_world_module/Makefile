obj-m := hello.o
# hello-objs := hello1.o hello2.o
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
# KERNELDIR ?= /usr/src/linux-headers-3.13.0-165-generic

PWD := $(shell pwd)

# CFLAGS += -g
ccflags-y += -g

all:
	make -C $(KERNELDIR) SUBDIRS=$(PWD) modules

clean:
	make -C $(KERNELDIR) SUBDIRS=$(PWD) clean
	
