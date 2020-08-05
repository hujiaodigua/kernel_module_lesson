#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/printk.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("GPL");

static struct pci_dev *_pdev;
static void __iomem *_mmio;

static const struct pci_device_id pcidevtbl[] = {

        { 0x6688, 0x0001, PCI_ANY_ID, PCI_ANY_ID, 0, 0, 0 },
        { } /* terminate */

};

void pci_helloworld_reset_pointer(void __iomem *mmio)
{
        iowrite8(1, mmio + 1);
}

void pci_helloworld_set_buf_len(void __iomem *mmio, uint8_t len)
{
        iowrite8(len, mmio + 2);
}

void pci_helloworld_write_char(void __iomem *mmio, char c)
{
        iowrite8(c, mmio + 0);
}

static int pci_helloworld_show(struct seq_file *m, void *v) {
        int i, len;
        char *buf;

        if (!_mmio) {
                pr_emerg("pci_iomap failed!\n");
                return -ENODEV;
        }

        pci_helloworld_reset_pointer(_mmio);

        len = ioread8(_mmio + 1);
        if (len) {
                buf = kmalloc(len + 1, GFP_KERNEL);
                if (!buf)
                        return -ENOMEM;
        } else {
                buf = "";
        }

        for (i = 0; i < len; i++)
                buf[i] = ioread8(_mmio);

        seq_printf(m, "%s", buf);

        return 0;
}

static int pci_helloworld_open(struct inode *inode, struct file *file) {
        return single_open(file, pci_helloworld_show, NULL);
}

ssize_t pci_helloworld_write (struct file *file, const char __user *buf, size_t len,
                        loff_t *l)
{
        int i = 0;

        if (!_mmio) {
                pr_emerg("failed to pci_iomap\n");
                return 0;
        }

        pci_helloworld_reset_pointer(_mmio);
        pci_helloworld_set_buf_len(_mmio, len + 1);

        for(i = 0; i < len; i ++)
                pci_helloworld_write_char(_mmio, buf[i]);

        return i;
}

static const struct file_operations proc_fops = {    // 读写释放等相关函数在这里填入
        .owner = THIS_MODULE,
        .open = pci_helloworld_open,
        .read = seq_read,
        .write = pci_helloworld_write,
        .llseek = seq_lseek,
        .release = single_release,
};

static int pci_helloworld_probe(struct pci_dev *pdev, const struct pci_device_id *ent)
{
        void __iomem *mmio;
        char *buf;
        int len, i;
        struct proc_dir_entry *proc_entry;

        pr_debug("probed pci dev, trying read.\n");

        mmio = pci_iomap(pdev, 0, 0);
        if (!mmio) {
                pr_emerg("failed to iomap!\n");
                return -ENODEV;
        }

        len = ioread8(mmio + 1);
        pr_info("length of string: %d bytes\n", len);

        buf = kmalloc(len + 1, GFP_KERNEL);
        if (!buf) {
                pr_err("no memory...\n");
                return -ENOMEM;
        }

        for (i = 0; i < len; i++)
                buf[i] = ioread8(mmio);

        pr_info("read this string: %s", buf);

        proc_entry = proc_create("helloworld", 0755, NULL, &proc_fops);    // proc_fops里注册entry相关函数

        _mmio = mmio;
        _pdev = pdev;
        return 0;
}

static void pci_helloworld_remove(struct pci_dev *pdev) {
        pr_debug("unloaded device\n");
}

static struct pci_driver helloworld_pci_driver = {            // 填入相关函数
        .name = "PCI-Hello-World driver",
        .id_table = pcidevtbl,
        .probe = pci_helloworld_probe,
        .remove = pci_helloworld_remove,

};

static int __init pci_helloworld_init(void)
{
        int rc;
        pr_debug("pci device driver online.\n");

        rc = pci_register_driver(&helloworld_pci_driver);    // 注册设备驱动
        if (rc) {
                pr_err("failed to register driver.\n");
                return rc;
        }

        return 0;
}

static void __exit pci_helloworld_exit(void)
{
        pr_debug("driver unloaded :-(\n");
        return;
}

module_init(pci_helloworld_init);
module_exit(pci_helloworld_exit);
