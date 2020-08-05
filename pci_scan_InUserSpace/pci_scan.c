#include <inttypes.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/io.h>     // inb/outb,etc...
 
#define PCI_CONFIG_ADDR 0xCF8
#define PCI_CONFIG_DATA 0xCFC
 
int pci_autodetect()
{
    uint32_t result;
    uint32_t io_addr;
    int function = 0;
    int bus = 0;
    int device = 0;
    int rev = 0;
    uint32_t vendor_id, dev_id, class1, class2, class3;
 
    for (bus = 0; bus<5; bus++)
    {
        for (device = 0; device<32; device++)
        {
            for(function = 0; function<8 ; function++ )
            {
                // 格式 31 Enabled 23:16 总线编号  15:11 设备编号 10:8 功能编号 7:2 配置空间寄存器编号 1:0 为0
                io_addr = 0x80000000 + (bus<<16) + (device<<11) + (function<<8);
                // 将地址写到CONFIG_ADDR寄存器
                outl(io_addr, PCI_CONFIG_ADDR);
                result = inl(PCI_CONFIG_DATA);    // 读data数据寄存器，得到id
                if (result != 0xffffffff)         // not the bad one print it
                {
                    vendor_id = result & 0xFFFF;
                    dev_id = result >> 16;
                    outl(io_addr+0x08, PCI_CONFIG_ADDR);
                    result = inl(PCI_CONFIG_DATA);
                    rev = result&0xff;
                    class3 = (result>>8)&0xff;
                    class2 = (result>>16)&0xff;
                    class1 = (result>>24)&0xff;
                    printf("0x%08x %02x:%02x.%x ", io_addr, bus, device, function);
                    // printf("PCI Read result: 0x%08x ioaddr: 0x%08x ", result, io_addr);
                    printf("Class %02x%02x: Device %04x:%04x (rev: %02x)\n", class1, class2, vendor_id, dev_id,rev);
                }
            }
        }
    }
    return 0;
}
 
int main(void)
{
    iopl(3);     // 必须要这句
    pci_autodetect();
    return 0;
}
