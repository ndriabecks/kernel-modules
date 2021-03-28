#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

MODULE_DESCRIPTION("Oops generating module");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Andrea Andreani");

#define READ 0
#define WRITE 1
#define OOPS WRITE

static int oops_init(void)
{
    int *a;

    a = (int*)0x00001234;

#if OOPS == WRITE
    *a = 3;
#elif
    printk(KERN_ALERT "value = %d\n", *a);
#else
#error "Unkown oops!"
#endif
    return 0;
}

static void my_oops_exit(void)
{
}

module_init(oops_init);
module_exit(my_oops_exit);