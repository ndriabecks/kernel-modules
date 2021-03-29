/**
 * @file   charmodule.c
 * @author Andrea Andreani
 * @date   28 March 2021
 * @version 0.1
 * @brief   An introductory character driver. This module maps to /dev/chrdev and
 * comes with a C program that can be run in Linux user space to communicate with
 * the LKM.
 */

#include <linux/init.h>         // Macros __init __exit
#include <linux/module.h>       // Core header for loading LKMs into the kernel
#include <linux/device.h>       // Header to support the kernel Driver Model
#include <linux/kernel.h>       // types, macros, functions for the kernel
#include <linux/fs.h>           // Header for the Linux file system support
#include <linux/uaccess.h>      // Required for the copy to user function
#include <linux/dev_printk.h>   // Printing macros

#define DEVICE_NAME "AAchardev"     // The device will appear at /dev/AAchardev
                                    // using this value
#define CLASS_NAME  "chr"           // The device's class
#define BUF_SIZE 128                // Size of the buffer 
#define MODULE_LOG "AAchardev: "    // The log shown in dmesg

MODULE_LICENSE("GPL");        
MODULE_AUTHOR("Andrea Andreani");    
MODULE_DESCRIPTION("A simple Linux char driver \
                    to understand how char drivers work");
MODULE_VERSION("0.1");            

static int majorNumber;             // Stores the device number
static char buffer[BUF_SIZE] = {0}; // Contains the messages
static short msg_size;              // Counts the size of the msg in buffer
static int opened = 0;              // Counts times that chrdev has been opened
static struct class *chrClass = NULL;
static struct device *chrDevice = NULL;

// Prototypes of the driver's functions
static int dev_open(struct inode *inodep, struct file *filep)
{
    return 0;
}

static int dev_release(struct inode *inodep, struct file *filep)
{
    return 0;
}

static ssize_t dev_write(struct file *filep, const char *buf, size_t buf_size,
                     loff_t * offset)
{
    return 0;
}

static ssize_t dev_read(struct file *filep, char *buf, size_t buf_size,
                    loff_t * offset)
{
    return 0;
}

/** @brief Devices are represented as files, the file_operations struct
 * stores the functions to associate with the operations in C99 syntax.
 * Check the README for more details.
 */
static struct file_operations fops = 
{
    .open = dev_open,
    .write = dev_write,
    .read = dev_read,
    .release = dev_release,
};

/** @brief This is the module's initialization function.
 *  @return returns 0 if succesful
 */
static int __init chrdev_init(void)
{
    printk( KERN_INFO MODULE_LOG "Initializing the chrdev\n");

    int err = 0;

    // Attempt to dynamically obtain a major number
    err = register_chrdev(0, DEVICE_NAME, &fops);
    if (err < 0) {
        pr_err(MODULE_LOG "Failed to register a major number");
        goto failed_majorNumber;
    }
    majorNumber = err;
    pr_info(MODULE_LOG "major number %d correctly registered\n", majorNumber);

    // Now let's register the device class
    chrClass = class_create(THIS_MODULE, CLASS_NAME);
    if (IS_ERR(chrClass)) {
        err = PTR_ERR(chrClass);
        pr_err(MODULE_LOG "Failed to register class\n");
        goto failed_class;
    }
    pr_info(MODULE_LOG "class correctly registered\n");

    // Device registration
    chrDevice = device_create(chrClass, NULL, MKDEV(majorNumber, 0), NULL, \
                        DEVICE_NAME);
    if (IS_ERR(chrDevice)) {
        err = PTR_ERR(chrDevice);
        pr_err(MODULE_LOG "Failed to create device\n");
        goto failed_device;
    }
    pr_info(MODULE_LOG "device correctly created\n");

    return 0;


failed_device:
    class_destroy(chrClass);
failed_class:
    unregister_chrdev(majorNumber, DEVICE_NAME);
failed_majorNumber:
    return err;
}

/* @brief The cleanup/exit function
 * It is similar to the init one.
 */
static void __exit chrdev_exit(void)
{
    device_destroy(chrClass, MKDEV(majorNumber, 0));
    class_unregister(chrClass);
    class_destroy(chrClass);
    unregister_chrdev(majorNumber, DEVICE_NAME);
    pr_info(MODULE_LOG "Module succesfully unloaded\n");
}

module_init(chrdev_init);
module_exit(chrdev_exit);