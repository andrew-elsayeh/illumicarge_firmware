#include "tests.h"
#include "zephyr/console/console.h"

void main(void)
{
	// test_adc_loop();
	while(1)
	{
		test_battery_monitor();	
		k_msleep(1000);

	}
}
