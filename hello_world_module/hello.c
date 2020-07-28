/*************************************************************************
	> File Name: hello_world.c
	> Author: 
	> Mail: 
	> Created Time: Mon 27 Jul 2020 06:19:41 PM +08
 ************************************************************************/

#include<linux/init.h>
#include<linux/module.h>

static char *whom = "world";
static int howmany = 1;

module_param(whom, charp, S_IRUGO);
module_param(howmany, int, S_IRUGO);

static int __init hello_init(void)
{
    int i;
    for (i = 0; i < howmany; i++)
        printk(KERN_ALERT "Hello %s\n", whom);

    return 0;
}

static void __exit hello_exit(void)
{
    printk(KERN_ALERT "Goodbye, cruel %s\n", whom);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("author");
MODULE_DESCRIPTION("description");
MODULE_VERSION("version_string");
