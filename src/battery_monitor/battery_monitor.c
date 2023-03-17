#include "battery_monitor.h"

#include <zephyr/sys/printk.h>
#include <zephyr/drivers/gpio.h>

#define MSP_STAT_NODE DT_ALIAS(mspstat)



/**
 * Private Methods
 */
void _private_method(void)
{
    return;
}

/**
 * Private Members
 */
ADCReader_t *_adc_reader = NULL;
BatteryMonitor_t *_battery_monitor_instance = NULL;
static const struct gpio_dt_spec mspstat = GPIO_DT_SPEC_GET(MSP_STAT_NODE, gpios);

/**
 * Public Methods
 */
int32_t getBatteryTemperature(void)
{
    int32_t adc_measurement = _adc_reader->getV_BAT_TEMP_ADC_mV(_adc_reader);

    int32_t calc = 5*(adc_measurement - 1000) /100;

    return calc;
}
int32_t getBatteryVoltage(void)
{
    int32_t adc_measurement = _adc_reader->getV_BAT_ADC_mV(_adc_reader);

    int32_t calc = (adc_measurement/3) +3300;

    return calc;
}
int32_t getBatteryCurrent(void)
{
    int32_t adc_measurement = _adc_reader->getBAT_CUR_mV(_adc_reader);

    int32_t calc = (adc_measurement -1250) /2;

    return calc;

}

bool getBatteryIsCharging(void)
{
    return gpio_pin_get_dt(&mspstat);
}

void initBatteryMonitor(BatteryMonitor_t *self, ADCReader_t *ADCReader)
{
    _adc_reader = ADCReader;
    self->ADCReader = ADCReader;
    self->getBatteryTemperature = getBatteryTemperature;
    self->getBatteryVoltage = getBatteryVoltage;
    self->getBatteryCurrent = getBatteryCurrent;
    self->getBatteryCurrent = getBatteryCurrent;
    self->getBatteryIsCharging = getBatteryIsCharging;

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