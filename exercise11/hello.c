#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/mutex.h>
#define DEVICE_NAME "meschar"
#define CLASS_NAME "mes"

static DEFINE_MUTEX(meschar_mutex);
static int majorNumber;
static struct class* mescharClass = NULL;
static struct device* mescharDevice = NULL;
static int timesCalled = 0;
static char message[256] = {0};
static short size_of_message;
static int being_used = 0;

static int device_open(struct inode *, struct file *);
static ssize_t device_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char __user *, size_t, loff_t *);
static int device_release(struct inode*, struct file *);

static struct file_operations fops = 
{
    .open = device_open,
    .read = device_read,
    .write = device_write,
    .release = device_release
};

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Abraham Lincoln");
MODULE_DESCRIPTION("Greatest module in the world!");
MODULE_VERSION("0.000001");

static int multiplier = 10;
module_param(multiplier, int, S_IRUGO);

static int __init hello_init(void){
    majorNumber = register_chrdev(0, DEVICE_NAME, &fops);
    mescharClass = class_create(THIS_MODULE, CLASS_NAME);
    mescharDevice = device_create(mescharClass, NULL, MKDEV(majorNumber, 0), NULL, DEVICE_NAME);
    printk(KERN_INFO "Oh hi mark - I love Lisa %dX more than you do\n", multiplier);
    mutex_init(&meschar_mutex);
    return 0;
}

static void __exit hello_exit(void){
    device_destroy(mescharClass, MKDEV(majorNumber,0));
    class_unregister(mescharClass);
    class_destroy(mescharClass);
    unregister_chrdev(majorNumber, DEVICE_NAME);
    mutex_destroy(&meschar_mutex);
    printk(KERN_INFO "sad, but still love Lisa %dX more than you\n", multiplier);
}

static int device_open(struct inode *inodep, struct file *filep){
  //  if (being_used) {
//	    printk(KERN_ALERT "im being used!\n");
//	    return 0;
    //}
    //being_used++;
    if (!mutex_trylock(&meschar_mutex)) {
	    printk(KERN_ALERT "I'm being used\n");
	    return -EBUSY;
    }
	timesCalled++;
    printk(KERN_INFO "You're tearing me apart, Lisa! Also I've been opened %d times.\n", timesCalled);
    return 0;
}


static ssize_t device_read(struct file *filep, char __user *buf, size_t length, loff_t *offset){
    long error_count;
    error_count = copy_to_user(buf, message, size_of_message);
    printk("Send %d characters bacck\n", size_of_message);
    return 0;
}

static ssize_t device_write(struct file *filep, const char __user *buf, size_t length, loff_t *offset){
    long error_count;
    printk("Running device_write\n");
    memset(message, 0, sizeof(message));
    error_count = copy_from_user(message,buf,length);
    size_of_message = strlen(message);
    printk(KERN_INFO "mesChar: Received %d characters from the user\n", size_of_message);
    printk(KERN_INFO "Message received: %s\n", message);
    return length;
}

static int device_release(struct inode *inodep, struct file *filep) {
    mutex_unlock(&meschar_mutex);
    //being_used--;
    printk("I'll never let go jack\n");
    return 0;
}


module_init(hello_init);
module_exit(hello_exit);

