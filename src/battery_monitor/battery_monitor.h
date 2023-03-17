#ifndef BATTERY_MONITOR_H
#define BATTERY_MONITOR_H


#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#include "../adc_reader/adc_reader.h"
#include "../gpio_controller/gpio_controller.h"

typedef struct BatteryMonitor BatteryMonitor_t;

struct BatteryMonitor {
    ADCReader_t *ADCReader;
    int32_t (*getBatteryTemperature) (void);
    int32_t (*getBatteryVoltage) (void);
    int32_t (*getBatteryCurrent) (void);
    bool (*getBatteryIsCharging) (void);

};


void initBatteryMonitor(BatteryMonitor_t *self, ADCReader_t *ADCReader, GPIOController_t *GPIOController);
#endif /* BATTERY_MONITOR_H */