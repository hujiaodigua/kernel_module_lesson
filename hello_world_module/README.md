## 应该如何使用modprobe:
1. cp hello.ko /lib/modules/3.13.0-165-generic/misc/ -- 首先将编译好的模块放入/lib/modules/'uname -r' 下  
1. depmod /lib/modules/3.13.0-165-generic/misc/hello.ko -- 用depmod更新modules.dep文件  
1. modprobe hello -- 使用modprobe装载模块 
1. dmesg -- 查看printk的打印信息
1. modprobe -r hello -- 使用modprobe卸载模块
