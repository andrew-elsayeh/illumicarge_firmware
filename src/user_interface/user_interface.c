#include "user_interface.h"


#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>



uint32_t led_brightness_percentage = 0;



/*
 * Get button configuration from the devicetree tl2 alias.
 */
#define TL2_NODE	DT_ALIAS(tl2)
#if !DT_NODE_HAS_STATUS(TL2_NODE, okay)
#error "Unsupported board: tl2 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec button_1 = GPIO_DT_SPEC_GET_OR(TL2_NODE, gpios,
							      {0});
static struct gpio_callback button_1_cb_data;


/*
 * Get button configuration from the devicetree tl3 alias.
 */
#define TL3_NODE	DT_ALIAS(tl3)
#if !DT_NODE_HAS_STATUS(TL2_NODE, okay)
#error "Unsupported board: tl3 devicetree alias is not defined"
#endif
static const struct gpio_dt_spec button_2 = GPIO_DT_SPEC_GET_OR(TL3_NODE, gpios,
							      {0});
static struct gpio_callback button_2_cb_data;


void button_1_pressed(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins)
{
    led_brightness_percentage = led_brightness_percentage + 10;
	// printk("Button pressed at %" PRIu32 "\n", k_cycle_get_32());

}
void button_2_pressed(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins)
{
    led_brightness_percentage = led_brightness_percentage - 10;
	// printk("Button pressed at %" PRIu32 "\n", k_cycle_get_32());

}


void _init_user_interface(void)
{
    int ret;


	if (!gpio_is_ready_dt(&button_1)) {
		printk("Error: button device %s is not ready\n",
		       button_1.port->name);
		return;
	}
	if (!gpio_is_ready_dt(&button_2)) {
		printk("Error: button device %s is not ready\n",
		       button_2.port->name);
		return;
	}


	ret = gpio_pin_configure_dt(&button_1, GPIO_INPUT);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",
		       ret, button_1.port->name, button_1.pin);
		return;
	}
	ret = gpio_pin_configure_dt(&button_2, GPIO_INPUT);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",
		       ret, button_2.port->name, button_2.pin);
		return;
	}

    

	ret = gpio_pin_interrupt_configure_dt(&button_1,
					      GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n",
			ret, button_1.port->name, button_1.pin);
		return;
	}

	gpio_init_callback(&button_1_cb_data, button_1_pressed, BIT(button_1.pin));
	gpio_add_callback(button_1.port, &button_1_cb_data);

	ret = gpio_pin_interrupt_configure_dt(&button_2,
					      GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n",
			ret, button_2.port->name, button_2.pin);
		return;
	}

	gpio_init_callback(&button_2_cb_data, button_2_pressed, BIT(button_2.pin));
	gpio_add_callback(button_2.port, &button_2_cb_data);

}



int32_t getLEDBrightnessPercentage(UserInterface_t *self)
{
    
    return led_brightness_percentage;
}

uint8_t initUserInterface(UserInterface_t *UserInterface)
{
    UserInterface->getLEDBrightnessPercentage = getLEDBrightnessPercentage;

    _init_user_interface();

    return 0;

}