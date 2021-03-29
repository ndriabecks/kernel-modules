#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/sched.h>

#define MODULE_LOG "[+] hello: "
#define VALUE_PERM S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andrea Andreani <aandreani1998@gmail.com");
MODULE_DESCRIPTION("My first attempt to code a kernel module");
MODULE_VERSION("0.0");

// This allows us to use parameters in the module
int value = -1;
module_param(value, int, VALUE_PERM);
MODULE_PARM_DESC(value, "Just a value");

// module_init will call this function
static int __init dummy_init(void)
{
    printk(KERN_INFO "Hello, AAmodule correctly loaded\n");

    printk(KERN_INFO MODULE_LOG "this is a correct print\n");
    printk(KERN_WARNING MODULE_LOG "value = %d\n", value);
    printk(KERN_WARNING MODULE_LOG "pid = %d\n", current->pid);
    pr_err(MODULE_LOG "Errore di prova\n");

    return 0;
}

// module_exit() will call this function
// OSS: this functions require you to put a return if
// not void
static void __exit dummy_exit(void)
{
    printk(KERN_WARNING MODULE_LOG "hello is being unloaded\n");
}

module_init(dummy_init);
module_exit(dummy_exit);