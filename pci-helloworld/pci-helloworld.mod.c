#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

__visible struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0xc7b3657, __VMLINUX_SYMBOL_STR(module_layout) },
	{ 0xe68be768, __VMLINUX_SYMBOL_STR(single_release) },
	{ 0x1d2e6f67, __VMLINUX_SYMBOL_STR(seq_read) },
	{ 0xfb8262ed, __VMLINUX_SYMBOL_STR(seq_lseek) },
	{ 0xa994554b, __VMLINUX_SYMBOL_STR(__pci_register_driver) },
	{ 0x28b068f8, __VMLINUX_SYMBOL_STR(seq_printf) },
	{ 0xf087137d, __VMLINUX_SYMBOL_STR(__dynamic_pr_debug) },
	{ 0x26543477, __VMLINUX_SYMBOL_STR(proc_create_data) },
	{ 0x12da5bb2, __VMLINUX_SYMBOL_STR(__kmalloc) },
	{ 0xf10de535, __VMLINUX_SYMBOL_STR(ioread8) },
	{ 0xf9c5aa4f, __VMLINUX_SYMBOL_STR(pci_iomap) },
	{ 0xc0a7cdfa, __VMLINUX_SYMBOL_STR(single_open) },
	{ 0x50eedeb8, __VMLINUX_SYMBOL_STR(printk) },
	{ 0x727c4f3, __VMLINUX_SYMBOL_STR(iowrite8) },
	{ 0xb4390f9a, __VMLINUX_SYMBOL_STR(mcount) },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "A0B647B26B02CF7579DA701");
