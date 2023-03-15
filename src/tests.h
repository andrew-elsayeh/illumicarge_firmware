#include <zephyr/kernel.h>

#include "adc_reader/adc_reader.h"

#include "user_interface/user_interface.h"

#include "pwm_controller/pwm_controller.h"

#include "power_path_controller/power_path_controller.h"


void clear_console(void);


void test_end_to_end_manual(void);

void test_adc(void);

void test_ui(void);

void test_pwm_controller(void);

void test_power_path_controller(void);

void test_end_to_end(void);

