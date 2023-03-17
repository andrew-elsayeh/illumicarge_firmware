#include "battery_monitor.h"

#include <zephyr/sys/printk.h>

#include "../gpio_controller/gpio_controller.h"


/**
 * Private Methods
 */


/**
 * Private Members
 */
static ADCReader_t *_adc_reader = NULL;
static GPIOController_t *_gpio_controller = NULL;

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
    return _gpio_controller->getMSP_STAT();
}

void initBatteryMonitor(BatteryMonitor_t *self, ADCReader_t *ADCReader, GPIOController_t *GPIOController)
{
    _adc_reader = ADCReader;
    _gpio_controller = GPIOController;

    self->ADCReader = ADCReader;
    self->getBatteryTemperature = getBatteryTemperature;
    self->getBatteryVoltage = getBatteryVoltage;
    self->getBatteryCurrent = getBatteryCurrent;
    self->getBatteryCurrent = getBatteryCurrent;
    self->getBatteryIsCharging = getBatteryIsCharging;



}