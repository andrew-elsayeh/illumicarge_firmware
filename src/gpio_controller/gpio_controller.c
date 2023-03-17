#include "gpio_controller.h"

#include <stdbool.h>

#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#include <zephyr/device.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#if !DT_NODE_EXISTS(DT_NODELABEL(load_switch))
#error "Overlay for power output node not properly defined."
#endif


#define MSP_STAT_NODE DT_ALIAS(mspstat)


static const struct gpio_dt_spec load_switch =
	GPIO_DT_SPEC_GET_OR(DT_NODELABEL(load_switch), gpios, {0});
static const struct gpio_dt_spec charging_switch =
	GPIO_DT_SPEC_GET_OR(DT_NODELABEL(charging_switch), gpios, {0});
static const struct gpio_dt_spec mspstat = GPIO_DT_SPEC_GET(MSP_STAT_NODE, gpios);




/**
 * Private Methods
 */
void _init_gpio_controller(void)
{
    int err;
	if (!gpio_is_ready_dt(&load_switch)) {
		printk("The load switch pin GPIO port is not ready.\n");
		return;
	}
	if (!gpio_is_ready_dt(&charging_switch)) {
		printk("The charging switch pin GPIO port is not ready.\n");
		return;
	}


    err = gpio_pin_configure_dt(&load_switch, GPIO_OUTPUT_INACTIVE);
	if (err != 0) {
		printk("Configuring GPIO pin failed: %d\n", err);
		return;
	}
    err = gpio_pin_configure_dt(&charging_switch, GPIO_OUTPUT_INACTIVE);
	if (err != 0) {
		printk("Configuring GPIO pin failed: %d\n", err);
		return;
	}

	if (!gpio_is_ready_dt(&mspstat)) {
		printk("Error: Device %s is not ready\n",
		       mspstat.port->name);
		return;
	}

    int ret = gpio_pin_configure_dt(&mspstat, GPIO_INPUT);
	if (ret != 0) {
		printk("Error %d: failed to configure %s pin %d\n",
		       ret, mspstat.port->name, mspstat.pin);
		return;
	}
}

/**
 * Private Members
 */
uint8_t _private_variable;


/**
 * Public Methods
 */
bool getMSP_STAT(void)
{
    return gpio_pin_get_dt(&mspstat);
}
void setLED1(bool state)
{
    return;
}
void setLED2(bool state)
{
    return;
}
void setLED3(bool state)
{
    return;
}
void setLED4(bool state)
{
    return;
}
void setEN2(bool state)
{
    int err;
    err = gpio_pin_set_dt(&load_switch, state);
	if (err != 0) {
		printk("Setting GPIO pin level failed: %d\n", err);
	}
}
void setPROG(bool state)
{
    if(state == true)
    {
        int err;
        err = gpio_pin_set_dt(&charging_switch, GPIO_OUTPUT_ACTIVE);
        if (err != 0) {
            printk("Setting GPIO pin level failed: %d\n", err);
        }
    }
    else
    {
        int err;
        err = gpio_pin_configure_dt(&charging_switch, GPIO_INPUT);
        if (err != 0) {
            printk("Configuring GPIO pin failed: %d\n", err);
            return;
        }
    }
}


void initGPIOController(GPIOController_t *self)
{
    self->getMSP_STAT = getMSP_STAT;
    self->setEN2 = setEN2;
    self->setLED1 = setLED1;
    self->setLED2 = setLED2;
    self->setLED3 = setLED3;
    self->setLED4 = setLED4;
    self->setPROG = setPROG;

    _init_gpio_controller();

}