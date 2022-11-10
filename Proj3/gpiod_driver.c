#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/kernel.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>
/* YOU WILL NEED OTHER HEADER FILES */

/* YOU WILL HAVE TO DECLARE SOME VARIABLES HERE */

/* ADD THE INTERRUPT SERVICE ROUTINE HERE */

// probe function
static int led_probe(/*INSERT*/)
{
	/*INSERT*/
	return 0;
}

// remove function
static int led_remove(/*INSERT*/)
{
	/* INSERT: Free the irq and print a message */
	return 0;
}

static struct of_device_id matchy_match[] = {
    {/*INSERT*/},
    {/* leave alone - keep this here (end node) */},
};

// platform driver object
static struct platform_driver adam_driver = {
	.probe	 = /*INSERT*/,
	.remove	 = /*INSERT*/,
	.driver	 = {
	       .name  = "The Rock: this name doesn't even matter",
	       .owner = THIS_MODULE,
	       .of_match_table = /*INSERT*/,
	},
};

module_platform_driver(/*INSERT*/);

MODULE_DESCRIPTION("424\'s finest");
MODULE_AUTHOR("GOAT");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:adam_driver");
