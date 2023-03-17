#include "tests.h"
#include "zephyr/console/console.h"

#include "adc_reader/adc_reader.h"
#include "user_interface/user_interface.h"
#include "pwm_controller/pwm_controller.h"
#include "power_path_controller/power_path_controller.h"
#include "battery_monitor/battery_monitor.h"

void main(void)
{	
	// test_end_to_end();

	PWMController_t PWMController;
	test_pwm_controller(&PWMController);

}
