/*************************************************************************
	> File Name: basic_code_structure.c
	> Author: 
	> Mail: 
	> Created Time: Fri 07 Aug 2020 06:30:54 PM +08
 ************************************************************************/

#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/cdev.h>
#include<linux/fs.h>
#include<linux/pci.h>
#include<linux/types.h>
#include<linux/string.h>


// 指明该驱动程序适用于哪一些PCI设备
static struct pci_device_id my_pci_tbl[] __initdata = {
    {PCI_VENDOR_ID, PCI_DEVICE_ID, PCI_ANY_ID, 0, 0, 0},
    {0, }
};

// 对特定PCI设备进行描述的数据结构
struct device_private{
    /*...*/
}

// 终端处理模块
static irqreturn_t device_interrupt(int irq, void *dev_id)
{
   /*...*/ 
}

// 设备文件操作接口
static struct file_operations device_fops = {
    owner:    THIS_MODULE,    // demo_fops所属的设备模块
    read:     device_read,    // 读设备操作
    write:    device_write,   // 写设备操作
    ioctl:    device_ioctl,   // 控制设备操作
    mmap:     device_mmap,    // 内存重映射操作
    open:     device_open,    // 打开设备操作
    releasel: device_release  // 释放设备操作
    /*...*/
};

// 设备模块信息
static struct pci_driver my_pci_driver = {
    name:     DEVICE_MODULE_NAME,  // 设备模块名称
    id_table: device_pci_tbl,      // 能够驱动的设备列表
    probe:    device_probe,        // 探测函数，查找并初始化设备
    remove:   device_remove        // 卸载设备模块
    /*...*/
};


static int __init init_module(void)
{
    /*...*/
}

static void __exit cleanup_module(void)
{
    pci_unregister_driver(&my_pci_driver);
}

// 加载驱动程序模块入口
module_init(init_modulet);

// 卸载驱动程序模块入口
module_exit(cleanup_module);
