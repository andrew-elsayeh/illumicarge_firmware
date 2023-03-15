#include "user_interface.h"


#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

/**
 * Defines
 */
#define TL2_NODE	DT_ALIAS(tl2)
#if !DT_NODE_HAS_STATUS(TL2_NODE, okay)
#error "Unsupported board: tl2 devicetree alias is not defined"
#endif
#define TL3_NODE	DT_ALIAS(tl3)
#if !DT_NODE_HAS_STATUS(TL2_NODE, okay)
#error "Unsupported board: tl3 devicetree alias is not defined"
#endif

#define STATUS_LED1_NODE DT_ALIAS(statusled1)
#define STATUS_LED2_NODE DT_ALIAS(statusled2)
#define STATUS_LED3_NODE DT_ALIAS(statusled3)
#define STATUS_LED4_NODE DT_ALIAS(statusled4)



/**
 * Public Methods
 */

void setStatusLEDs( uint32_t percentage);
uint32_t getUserInputLEDBrightnessPercent(void);


/**
 * Private Methods
 */

void _init_user_buttons(void);
void _init_pwms(void);
void _init_user_interface(void);
void _init_status_leds(void);

void _button_1_cb(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins);
void _button_2_cb(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins);



/**
 * Private Members
 */
uint32_t user_input_led_brightness_percent;
PWMController_t *_PWMController = NULL;



static const struct gpio_dt_spec button_1 = GPIO_DT_SPEC_GET_OR(TL2_NODE, gpios,
							      {0});
static struct gpio_callback button_1_cb_data;

static const struct gpio_dt_spec button_2 = GPIO_DT_SPEC_GET_OR(TL3_NODE, gpios,
							      {0});
static struct gpio_callback button_2_cb_data;


static const struct gpio_dt_spec statusled1 = GPIO_DT_SPEC_GET(STATUS_LED1_NODE, gpios);
static const struct gpio_dt_spec statusled2 = GPIO_DT_SPEC_GET(STATUS_LED2_NODE, gpios);
static const struct gpio_dt_spec statusled3 = GPIO_DT_SPEC_GET(STATUS_LED3_NODE, gpios);
static const struct gpio_dt_spec statusled4 = GPIO_DT_SPEC_GET(STATUS_LED4_NODE, gpios);



void _button_1_cb(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins)
{
    if(user_input_led_brightness_percent < 100)
    {
        user_input_led_brightness_percent = user_input_led_brightness_percent + 25;
    }

    if(_PWMController != NULL)
    {
        _PWMController->setLEDBrightness(user_input_led_brightness_percent);
    }

}

void _button_2_cb(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins)
{
    if(user_input_led_brightness_percent > 0)
    {
        user_input_led_brightness_percent = user_input_led_brightness_percent - 25;
    }

    if(_PWMController != NULL)
    {
        _PWMController->setLEDBrightness(user_input_led_brightness_percent);
    }

}


void _init_user_buttons(void)
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

	gpio_init_callback(&button_1_cb_data, _button_1_cb, BIT(button_1.pin));
	gpio_add_callback(button_1.port, &button_1_cb_data);

	ret = gpio_pin_interrupt_configure_dt(&button_2,
					      GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n",
			ret, button_2.port->name, button_2.pin);
		return;
	}

	gpio_init_callback(&button_2_cb_data, _button_2_cb, BIT(button_2.pin));
	gpio_add_callback(button_2.port, &button_2_cb_data);


}

void _init_status_leds(void)
{

    if (!gpio_is_ready_dt(&statusled1)) {
		printk("Error LED\n");
	}
    if (!gpio_is_ready_dt(&statusled2)) {
		printk("Error LED\n");
	}
    if (!gpio_is_ready_dt(&statusled3)) {
		printk("Error LED\n");
	}
    if (!gpio_is_ready_dt(&statusled4)) {
		printk("Error LED\n");
	}

    gpio_pin_configure_dt(&statusled1, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&statusled2, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&statusled3, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&statusled4, GPIO_OUTPUT_INACTIVE);

}

void _init_user_interface(void)
{

    _init_user_buttons();
    _init_status_leds();

}





void setStatusLEDs( uint32_t percentage)
{
    if(percentage < 10)
    {
     gpio_pin_set_dt(&statusled1, 0);   
     gpio_pin_set_dt(&statusled2, 0);   
     gpio_pin_set_dt(&statusled3, 0);   
     gpio_pin_set_dt(&statusled4, 0);
     return;   
    }
    if(percentage <= 25)
    {
     gpio_pin_set_dt(&statusled1, 1);   
     gpio_pin_set_dt(&statusled2, 0);   
     gpio_pin_set_dt(&statusled3, 0);   
     gpio_pin_set_dt(&statusled4, 0);
     return;   
    }
    if(percentage <= 50)
    {
     gpio_pin_set_dt(&statusled1, 1);   
     gpio_pin_set_dt(&statusled2, 1);   
     gpio_pin_set_dt(&statusled3, 0);   
     gpio_pin_set_dt(&statusled4, 0);  
     return;
    }
    if(percentage <= 75)
    {
     gpio_pin_set_dt(&statusled1, 1);   
     gpio_pin_set_dt(&statusled2, 1);   
     gpio_pin_set_dt(&statusled3, 1);   
     gpio_pin_set_dt(&statusled4, 0);  
          return;
    }
    if(percentage > 90)
    {
     gpio_pin_set_dt(&statusled1, 1);   
     gpio_pin_set_dt(&statusled2, 1);   
     gpio_pin_set_dt(&statusled3, 1);   
     gpio_pin_set_dt(&statusled4, 1);  
          return;
    }
    
}

uint32_t getUserInputLEDBrightnessPercent(void)
{
    return user_input_led_brightness_percent;
}

void initUserInterface(UserInterface_t *self, PWMController_t *PWMController)
{
    self->PWMController = PWMController;
    self->user_input_led_brightness_percent = 0;
    self->setStatusLEDs = setStatusLEDs;
    self->getUserInputLEDBrightnessPercent = getUserInputLEDBrightnessPercent;

    _PWMController = PWMController;
    _init_user_interface();

}