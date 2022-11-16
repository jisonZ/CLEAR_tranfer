#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/kernel.h>
#include <linux/gpio/consumer.h>
#include <linux/platform_device.h>
/* YOU WILL NEED OTHER HEADER FILES */
#include <linux/interrupt.h>
/* YOU WILL HAVE TO DECLARE SOME VARIABLES HERE */
struct gpio_desc *led, *button;
int irq_num;

/* ADD THE INTERRUPT SERVICE ROUTINE HERE */
// the Interrupt Service Routine (AKA interrupt handler)
// is executed when an interrupt happens
static irq_handler_t led_handler(unsigned int irq, void* dev_id, struct pt_regs* regs) {
	printk(KERN_INFO "ADAM_DRIVER: irq was triggered\n");
	// when button iterrupt is detected, switch led lighting condition
	int ledCond = gpiod_get_value(led);
	if (ledCond == 1) {
		gpiod_set_value(led, 0);
	} else {
		gpiod_set_value(led, 1);
	}
	return (irq_handler_t) IRQ_HANDLED;
}	

// probe function
static int led_probe(struct platform_device *pdev)
{
	// Print to Kernel
	printk(KERN_INFO "ADAM_DRIVER: led probe\n");
	
	// Initialize pointers that represent the GPIO pin for LED and Button 
	led = devm_gpiod_get_index(&pdev->dev, "haochenz", 0, GPIOD_OUT_LOW);
	button = devm_gpiod_get_index(&pdev->dev, "haochenz", 1, GPIOD_IN);
	
	// set button debounce
	gpiod_set_debounce(button, 100);

	// issue the button pointer a irq number
	irq_num = gpiod_to_irq(button);

	// register the led_handler with irq number, trigger condition is high
	if (request_irq(irq_num, (irq_handler_t)led_handler, IRQF_TRIGGER_RISING, "randomName", NULL) !=0) {
		printk(KERN_INFO "ADAM_DRIVER: ISR register failed\n");
		return -1;
	}

	return 0;
}

// remove function
static int led_remove(struct platform_device *pdev)
{
	printk(KERN_INFO "ADAM_DRIVER: led_remove\n");
	free_irq((irq_handler_t)led_handler, NULL);
	return 0;
}

static struct of_device_id matchy_match[] = {
    {.compatible = "FormulaOne",},
    {/* leave alone - keep this here (end node) */},
};

// platform driver object
static struct platform_driver adam_driver = {
	.probe	 = led_probe,
	.remove	 = led_remove,
	.driver	 = {
	       .name  = "The Rock: this name doesn't even matter",
	       .owner = THIS_MODULE,
	       .of_match_table = matchy_match,
	},
};

module_platform_driver(adam_driver);

MODULE_DESCRIPTION("424\'s finest");
MODULE_AUTHOR("GOAT");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:adam_driver");
