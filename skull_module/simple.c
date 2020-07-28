/*************************************************************************
	> File Name: simple.c
	> Author: 
	> Mail: 
	> Created Time: Tue 28 Jul 2020 11:53:25 AM +08
 ************************************************************************/

#include<linux/module.h>
#include<linux/moduleparam.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/types.h>
#include<linux/file.h>
#include<linux/cdev.h>

#include<linux/device.h>

#include<linux/blkdev.h>
#include<linux/sysctl.h>
#include<linux/seq_file.h>
#include<linux/fs.h>
#include<linux/poll.h>
#include<linux/ctype.h>
#include<linux/string.h>
#include<linux/hdreg.h>
#include<linux/proc_fs.h>
#include<linux/random.h>
#include<linux/module.h>
#include<linux/reboot.h>
#include<linux/file.h>
#include<linux/compat.h>
#include<linux/delay.h>
#include<linux/slab.h>

static int simple_major = 0;
module_param(simple_major, int, 0);
MODULE_AUTHOR("Jonathan Corbet");
MODULE_LICENSE("Dual BSD/GPL");

// open the device; in fact, there is nothing to do here
int simple_open(struct inode *inode, struct file *filp)
{
    return 0;
}

// closing is just as simpler
int simple_release(struct inode *inode, struct file *filp)
{
    return 0;
}

static char *content = "hello, i am simple char dev! \n";

ssize_t simple_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
    int copied;
    if (*ppos >= strlen(content))
        return 0;

    copied = strlen(content) - *ppos;

    if (copied > size)
        copied = size;

    copy_to_user(buf, content + *ppos, copied);
    
    *ppos += copied;

    return copied;
}

struct file_operations simple_fops = {
    .owner   = THIS_MODULE,
    .open    = simple_open,
    .read    = simple_read,
    .release = simple_release,
};

static struct cdev simple_dev;

// Module housekeeping.
static int simple_init(void)
{
    int result;
    dev_t dev = MKDEV(simple_major, 0);

    // figure out our device number
    if (simple_major)
    {
        result = register_chrdev_region(dev, 1, "simple");
    }
    else
    {
        result = alloc_chrdev_region(&dev, 0, 1, "simple");
        simple_major = MAJOR(dev);
    }

    if (result < 0)
    {
        printk(KERN_WARNING "simple: unable to get major %d\n", simple_major);
        return result;
    }

    // now set up cdev
    cdev_init(&simple_dev, &simple_fops);
    simple_dev.owner = THIS_MODULE;
    result = cdev_add (&simple_dev, dev, 1);    // 添加到设备树里
    // fail gracefully if need be
    if (result)
        printk(KERN_NOTICE "Error %d adding simple", result);
    return 0;
}

static void simple_cleanup(void)
{
    cdev_del(&simple_dev);
    unregister_chrdev_region(MKDEV(simple_major, 0), 1);
}

module_init(simple_init);
module_exit(simple_cleanup);

