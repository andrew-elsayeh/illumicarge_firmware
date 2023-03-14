#include "user_interface.h"


#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/sys/util.h>
#include <zephyr/sys/printk.h>
#include <inttypes.h>

#include <zephyr/drivers/pwm.h>

/*
 * Get button configuration from the devicetree tl2 alias.
 */
#define TL2_NODE	DT_ALIAS(tl2)
#if !DT_NODE_HAS_STATUS(TL2_NODE, okay)
#error "Unsupported board: tl2 devicetree alias is not defined"
#endif


/*
 * Get button configuration from the devicetree tl3 alias.
 */
#define TL3_NODE	DT_ALIAS(tl3)
#if !DT_NODE_HAS_STATUS(TL2_NODE, okay)
#error "Unsupported board: tl3 devicetree alias is not defined"
#endif


#define STATUS_LED1_NODE DT_ALIAS(statusled1)
#define STATUS_LED2_NODE DT_ALIAS(statusled2)
#define STATUS_LED3_NODE DT_ALIAS(statusled3)
#define STATUS_LED4_NODE DT_ALIAS(statusled4)




// Public Methods
void setLEDPWM( uint32_t percentage);
int32_t getLEDBrightnessPercentage(UserInterface_t *self);
////////////////////


//Private Methods
void _init_user_buttons(void);
void _init_pwms(void);
void _init_user_interface(void);
void _init_status_leds(void);

void _button_1_cb(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins);
void _button_2_cb(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins);
////////////////////



// Public Members////////////////////
////////////////////////////////////////



// Private Members//
uint32_t led_brightness_percentage = 0;


static const struct pwm_dt_spec pwm_led0 = PWM_DT_SPEC_GET(DT_ALIAS(pwm_led0));


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
////////////////////


void _button_1_cb(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins)
{
    if(led_brightness_percentage < 100)
    {
        led_brightness_percentage = led_brightness_percentage + 25;
    }
    setLEDPWM(led_brightness_percentage);

}
void _button_2_cb(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins)
{
    if(led_brightness_percentage > 0)
    {
        led_brightness_percentage = led_brightness_percentage - 25;
    }
    setLEDPWM(led_brightness_percentage);

    gpio_pin_toggle_dt(&statusled1);
    gpio_pin_toggle_dt(&statusled2);
    gpio_pin_toggle_dt(&statusled3);
    gpio_pin_toggle_dt(&statusled4);

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

void _init_pwms(void)
{
	if (!device_is_ready(pwm_led0.dev)) {
		printk("Error: PWM device %s is not ready\n",
		       pwm_led0.dev->name);
	}
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

    gpio_pin_configure_dt(&statusled1, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&statusled2, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&statusled3, GPIO_OUTPUT_ACTIVE);
    gpio_pin_configure_dt(&statusled4, GPIO_OUTPUT_ACTIVE);



    // gpio_pin_set_dt(&statusled1, 0);
    // gpio_pin_set_dt(&statusled2, 0);
    // gpio_pin_set_dt(&statusled3, 0);
    // gpio_pin_set_dt(&statusled4, 0);
}

void _init_user_interface(void)
{

    _init_user_buttons();
    _init_pwms();
    _init_status_leds();

}



int32_t getLEDBrightnessPercentage(UserInterface_t *self)
{
    
    return led_brightness_percentage;
}

void setLEDPWM( uint32_t percentage)
{
    uint32_t pulse_width = pwm_led0.period * percentage / 100;
    pwm_set_pulse_dt(&pwm_led0, pulse_width);
}

uint8_t initUserInterface(UserInterface_t *UserInterface)
{
    UserInterface->getLEDBrightnessPercentage = getLEDBrightnessPercentage;
    UserInterface->setLEDPWM = setLEDPWM;

    _init_user_interface();

    return 0;

}