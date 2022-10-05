#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
//do a hash define string for DEVICE_NAME (choose a name)
#define DEVICE_NAME jz118device
//do a hash define string for CLASS_NAME (choose  a name)
#define CLASS_NAME jz118class
// Choose a variable name to describe the major number; don't initialize the
// value
static int majorNum;

// Choose variable names to describe the class and device pointers
// Set both equal to NULL
static struct class* = NULL;
static struct device* = NULL;

// Here we declare the device_open function that will be called by the open
// system call; No need to change anything here
static int device_open(struct inode *, struct file *);

static struct file_operations fops =
{
	.open = device_open
		//Throw the device_open function reference here - this may help:
					//https://stackoverflow.com/a/46138031
};

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abraham Lincoln");
MODULE_DESCRIPTION("Greatest module in the world!");
MODULE_VERSION("0.000001");

static int multiplier = 10;
module_param(multiplier, int, S_IRUGO);

static int __init hello_init(void){
	  // Replace HAHA with device name macro defined earlier
    majorNumber = register_chrdev(0, DEVICE_NAME , &fops);
		// Replace YOLO with class name macro defined earlier
    mescharClass = class_create(THIS_MODULE, CLASS_NAME);
		// Replace DOGE with class pointer, DONKEY with major number variable, and
		// CRYPTO with device name macro defined earlier
    mescharDevice = device_create(class, NULL, MKDEV(majorNum, 0), NULL, majorNum);
    printk(KERN_INFO "Oh hi mark - I love Lisa %dX more than you do\n", multiplier);
    return 0;
}

static void __exit hello_exit(void){
	  // Replace VIBE with class pointer, LOL with major number variable, and
		// SWAG with device name macro defined earlier
    device_destroy(class, MKDEV(majorNum,0));
    class_unregister(class);
    class_destroy(class);
    unregister_chrdev(majorNum, DEVICE_NAME);
    printk(KERN_INFO "sad, but still love Lisa %dX more than you\n", multiplier);
}

static int device_open(struct inode *inodep, struct file *filep){
    printk(KERN_INFO "You’re tearing me apart, Lisa!\n");
    return 0;
}

module_init(hello_init);
module_exit(hello_exit);
