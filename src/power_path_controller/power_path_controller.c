#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>


#include "power_path_controller.h"

/**
 * Private Methods
 */



/**
 * Private Members
 */


/**
 * Class Public Methods
 */
void setLoad(bool status);
bool getLoadStatus(void);

void setBatteryCharger(bool status);
bool getBatteryChargerStatus(void);



void initPowerPathController(PowerPathController_t *self)
{


}