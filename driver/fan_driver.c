#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

static int __init fan_driver_init(void)
{
    printk(KERN_INFO "Fan Driver: Module loaded\n");
    return 0;
}

static void __exit fan_driver_exit(void)
{
    printk(KERN_INFO "Fan Driver: Module unloaded\n");
}

module_init(fan_driver_init);
module_exit(fan_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ayush");
MODULE_DESCRIPTION("Virtual Smart Home Fan Driver");