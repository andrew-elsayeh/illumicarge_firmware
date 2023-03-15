#include "pwm_controller.h"


#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include <zephyr/drivers/pwm.h>



/**
 * Private Methods
 */
void _init_pwms(void);



/**
 * Private Members
 */
static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));
uint32_t led_brightness_percentage;



void _init_pwms(void)
{
	if (!device_is_ready(pwm_led0.dev)) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_led0.dev->name);
	}
}


int32_t getLEDBrightnessPercentage(void)
{
    
    return led_brightness_percentage;
}

void setLEDBrightness( uint32_t percentage)
{
    uint32_t pulse_width = pwm_led0.period * percentage / 100;
    pwm_set_pulse_dt(&pwm_led0, pulse_width);
    
}

void initPWMController(PWMController_t *self)
{
    self->getLEDBrightnessPercentage = getLEDBrightnessPercentage;
    self->setLEDBrightness = setLEDBrightness;

    _init_pwms();

}