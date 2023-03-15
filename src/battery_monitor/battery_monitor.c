#include "battery_monitor.h"

#include <zephyr/sys/printk.h>

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
    return true;
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
}