#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("haochenz");
MODULE_DESCRIPTION("this is description");
MODULE_VERSION("0.00001");

static int multiplier = 10;
module_param(multiplier, int, S_IRUGO);

static int __init hello_init(void) {
	int i = 0;
	for (i = 0; i < multiplier; ++i) {
		printk(KERN_INFO "oh hi mark\n");
	}
	return 0;

}

static void __exit hello_exit(void) {
	int i = 0;
	for (i = 0; i < multiplier; ++i) {
	printk(KERN_INFO "sad, but love you\n");

	}
}
module_init(hello_init);
module_exit(hello_exit);
