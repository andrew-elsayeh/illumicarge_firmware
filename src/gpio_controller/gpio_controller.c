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


#define MSP_STAT_NODE DT_ALIAS(mspstat)

/**
 * Private Members
 */
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
static const struct gpio_dt_spec load_switch =
	GPIO_DT_SPEC_GET_OR(DT_NODELABEL(load_switch), gpios, {0});
static const struct gpio_dt_spec charging_switch =
	GPIO_DT_SPEC_GET_OR(DT_NODELABEL(charging_switch), gpios, {0});

static const struct gpio_dt_spec mspstat = GPIO_DT_SPEC_GET(MSP_STAT_NODE, gpios);



/**
 * Private Methods
 */
void _init_gpio_controller(void);

void _init_ppc_gpios(void);
void _init_battery_monitor_gpios(void);
void _init_ui_gpios(void);

void _button_1_cb(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins);

void _button_2_cb(const struct device *dev, struct gpio_callback *cb,
		    uint32_t pins);


void _init_ui_gpios(void)
{
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


	int ret = gpio_pin_configure_dt(&button_1, GPIO_INPUT);
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


	ret = gpio_pin_interrupt_configure_dt(&button_1,
					      GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n",
			ret, button_1.port->name, button_1.pin);
		return;
	}

	ret = gpio_pin_interrupt_configure_dt(&button_2,
					      GPIO_INT_EDGE_TO_ACTIVE);
	if (ret != 0) {
		printk("Error %d: failed to configure interrupt on %s pin %d\n",
			ret, button_2.port->name, button_2.pin);
		return;
	}



}



void _init_battery_monitor_gpios(void)
{
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


void _init_ppc_gpios(void)
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
    err = gpio_pin_configure_dt(&charging_switch, GPIO_INPUT);
	if (err != 0) {
		printk("Configuring GPIO pin failed: %d\n", err);
		return;
	}
}

void _init_gpio_controller(void)
{

	_init_ppc_gpios();
	_init_battery_monitor_gpios();
	_init_ui_gpios();

}






/**
 * Public Methods
 */
bool getMSP_STAT(void)
{
    return gpio_pin_get_dt(&mspstat);
}
void setLED1(bool state)
{
     gpio_pin_set_dt(&statusled1, state);   
}
void setLED2(bool state)
{
     gpio_pin_set_dt(&statusled2, state);   
}
void setLED3(bool state)
{
     gpio_pin_set_dt(&statusled3, state);   
}
void setLED4(bool state)
{
     gpio_pin_set_dt(&statusled4, state);
}

void setEN2(bool state)
{
    gpio_pin_set_dt(&load_switch, state);
}

void setPROG(bool state)
{
    if(state == true)
    {
        // int err;
		gpio_pin_configure_dt(&charging_switch, GPIO_OUTPUT_ACTIVE);
        // err = gpio_pin_set_dt(&charging_switch, GPIO_OUTPUT_ACTIVE);
        // if (err != 0) {
        //     printk("Setting GPIO pin level failed: %d\n", err);
        // }
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

void addBTN1Interrupt(void (* callback))
{
	gpio_init_callback(&button_1_cb_data, callback, BIT(button_1.pin));
	gpio_add_callback(button_1.port, &button_1_cb_data);
}

void addBTN2Interrupt(void (* callback))
{

	gpio_init_callback(&button_2_cb_data, callback, BIT(button_2.pin));
	gpio_add_callback(button_2.port, &button_2_cb_data);
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
    self->addBTN1Interrupt = addBTN1Interrupt;
    self->addBTN2Interrupt = addBTN2Interrupt;
    _init_gpio_controller();

}