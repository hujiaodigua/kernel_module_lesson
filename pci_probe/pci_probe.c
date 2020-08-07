/*************************************************************************
	> File Name: pci_probe.c
	> Author: 
	> Mail: 
	> Created Time: Wed 05 Aug 2020 07:25:18 PM +08
 ************************************************************************/

#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>

#include<linux/cdev.h>
#include<linux/fs.h>
#include<asm/uaccess.h>

#include<linux/types.h>
#include<linux/errno.h>
#include<linux/string.h>

#include<linux/slab.h>
#include<linux/pci.h>

#ifndef LL_DEBUG
#define LL_DEBUG
#endif

#ifdef LL_DEBUG

// KERN_INFO
#define ll_debug(fmt, ...) printk(KERN_INFO "[++LL debug: %d @ %s]: " fmt, __LINE__, __func__, ##__VA_ARGS__)
#else
#define ll_debug(fmt, ...)
#endif

// #define TEST_CHAR
#ifdef TEST_CHAR
extern int foodrv_probe(void);
extern int foodrv_remove(void);
#endif

// SMBus Port

