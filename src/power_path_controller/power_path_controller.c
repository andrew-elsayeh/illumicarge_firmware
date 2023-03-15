
#include <zephyr/devicetree.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>

#include <zephyr/device.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>


#include "power_path_controller.h"

/**
 * Private Methods
 */
void _init_power_path_controller(void);


/**
 * Private Members
 */
bool load_status;
bool battery_charger_status;

#if !DT_NODE_EXISTS(DT_NODELABEL(load_switch))
#error "Overlay for power output node not properly defined."
#endif

static const struct gpio_dt_spec load_switch =
	GPIO_DT_SPEC_GET_OR(DT_NODELABEL(load_switch), gpios, {0});
static const struct gpio_dt_spec charging_switch =
	GPIO_DT_SPEC_GET_OR(DT_NODELABEL(charging_switch), gpios, {0});

/**
 * Class Public Methods
 */
void setLoad(bool status);

void setBatteryCharger(bool status);


void _init_power_path_controller(void)
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
    
}
void setLoad(bool status)
{	
    int err;
    err = gpio_pin_set_dt(&load_switch, status);
	if (err != 0) {
		printk("Setting GPIO pin level failed: %d\n", err);
	}
}

void setBatteryCharger(bool status)
{
    int err;
	if (status == true)	//if the battery should charge
	{
		err = gpio_pin_configure_dt(&charging_switch, GPIO_INPUT);
		if (err != 0) {
			printk("Configuring GPIO pin failed: %d\n", err);
			return;
		}
	}
	else if (status == false)
	{	
		err = gpio_pin_configure_dt(&charging_switch, GPIO_OUTPUT_INACTIVE);
		if (err != 0) {
			printk("Setting Battery Charger Failed: %d\n", err);
		}

	}
	
}



void initPowerPathController(PowerPathController_t *self)
{
    self->setBatteryCharger = setBatteryCharger;
    self->setLoad = setLoad;

    _init_power_path_controller();


}