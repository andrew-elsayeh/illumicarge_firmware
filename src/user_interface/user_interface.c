#include "user_interface.h"

#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>



/**
 * Defines
 */




/**
 * Public Methoods
 */

void setStatusLEDs( uint32_t percentage);
uint32_t getUserInputLEDBrightnessPercent(void);


/**
 * Private Methods
 */

void _init_user_interface(void);

void _button_1_cb(void);
void _button_2_cb(void);



/**
 * Private Members
 */
static uint32_t _user_input_led_brightness_percent;
static PWMController_t *_pwm_controller = NULL;
static GPIOController_t *_gpio_controller = NULL;





#define BRIGHTNESS_STEP 10

void _button_1_cb(void)
{
    if(_user_input_led_brightness_percent < 100)
    {
        _user_input_led_brightness_percent = _user_input_led_brightness_percent + BRIGHTNESS_STEP;
    }

    if(_pwm_controller != NULL)
    {
        _pwm_controller->setLEDBrightness(_user_input_led_brightness_percent);
    }

}

void _button_2_cb(void)
{
    if(_user_input_led_brightness_percent > 0)
    {
        _user_input_led_brightness_percent = _user_input_led_brightness_percent - BRIGHTNESS_STEP;
    }

    if(_pwm_controller != NULL)
    {
        _pwm_controller->setLEDBrightness(_user_input_led_brightness_percent);
    }

}

void _init_user_interface(void)
{
    _gpio_controller->configureBTN1Interrupt(_button_1_cb);
    _gpio_controller->configureBTN2Interrupt(_button_2_cb);
}





void setStatusLEDs( uint32_t percentage)
{
    if(percentage < 10)
    {
        _gpio_controller->setLED1(0);
        _gpio_controller->setLED2(0);
        _gpio_controller->setLED3(0);
        _gpio_controller->setLED4(0);
        return;   
    }
    if(percentage <= 25)
    {
        _gpio_controller->setLED1(1);
        _gpio_controller->setLED2(0);
        _gpio_controller->setLED3(0);
        _gpio_controller->setLED4(0);
        return;   
    }
    if(percentage <= 50)
    {
        _gpio_controller->setLED1(1);
        _gpio_controller->setLED2(1);
        _gpio_controller->setLED3(0);
        _gpio_controller->setLED4(0);
        return;   
    }
    if(percentage <= 75)
    {
        _gpio_controller->setLED1(1);
        _gpio_controller->setLED2(1);
        _gpio_controller->setLED3(1);
        _gpio_controller->setLED4(0);
        return;   
    }
    if(percentage > 90)
    {
        _gpio_controller->setLED1(1);
        _gpio_controller->setLED2(1);
        _gpio_controller->setLED3(1);
        _gpio_controller->setLED4(1);
        return;   
    }
    
}

uint32_t getUserInputLEDBrightnessPercent(void)
{
    return _user_input_led_brightness_percent;
}

void initUserInterface(UserInterface_t *self, PWMController_t *PWMController, GPIOController_t *GPIOController)
{
    self->setStatusLEDs = setStatusLEDs;
    self->getUserInputLEDBrightnessPercent = getUserInputLEDBrightnessPercent;

    _pwm_controller = PWMController;
    _gpio_controller = GPIOController;

    _init_user_interface();

}