
#include "adc_reader/adc_reader.h"
#include "user_interface/user_interface.h"
#include "pwm_controller/pwm_controller.h"
#include "power_path_controller/power_path_controller.h"
#include "battery_monitor/battery_monitor.h"


void clear_console(void);

void test_end_to_end(void);

//Unit Tests

void test_gpio_controller(GPIOController_t *GPIOController);

void test_adc(ADCReader_t *ADCReader);
void test_adc_loop(ADCReader_t *ADCReader);

void test_pwm_controller(PWMController_t *PWMController);

void test_power_path_controller(GPIOController_t *GPIOController, PowerPathController_t *PowerPathController);

void test_ui_loop(UserInterface_t *UserInterface, GPIOController_t *GPIOController, PWMController_t *PWMController);

void test_battery_monitor(BatteryMonitor_t *BatteryMonitor, ADCReader_t *ADCReader, GPIOController_t *GPIOController);
void test_battery_monitor_loop(BatteryMonitor_t *BatteryMonitor, ADCReader_t *ADCReader, GPIOController_t *GPIOController);




