
#include <zephyr/sys/printk.h>

#include <inttypes.h>

#include "power_path_controller.h"
#include "../gpio_controller/gpio_controller.h"

/**
 * Private Methods
 */
void _init_power_path_controller(void);


/**
 * Private Members
 */
bool load_status;
bool battery_charger_status;

static GPIOController_t *_gpio_controller;
/**
 * Class Public Methods
 */
void setLoad(bool status);

void setBatteryCharger(bool status);


void _init_power_path_controller(void)
{
	return;
    
}
void setLoad(bool state)
{	
	_gpio_controller->setEN2(state);

}

void setBatteryCharger(bool charging)
{
	if(charging == false)
	{
		_gpio_controller->setPROG(true);
	}
	else
	{
		_gpio_controller->setPROG(false);
	}

}



void initPowerPathController(PowerPathController_t *self, GPIOController_t *gpio_controller)
{
    self->setBatteryCharger = setBatteryCharger;
    self->setLoad = setLoad;

	_gpio_controller = gpio_controller;

    _init_power_path_controller();


}