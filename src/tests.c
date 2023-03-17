/*
 * Copyright (c) 2020 Libre Solar Technologies GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>

#include "tests.h"

#include "adc_reader/adc_reader.h"
#include "user_interface/user_interface.h"
#include "pwm_controller/pwm_controller.h"
#include "power_path_controller/power_path_controller.h"
#include "battery_monitor/battery_monitor.h"

void test_end_to_end(void)
{

	printk("\nEnd to End Test: ADC \n");

	//Run ADC test 10 times in 5 seconds
	int64_t cur_time = k_uptime_get(); 
	while(k_uptime_get() < cur_time + 5000)
	{
		test_adc();
		k_msleep(500);
	}

	//Run PWM Controller Test once
	printk("\nEnd to End Test:  PWM Controller\n");
	test_pwm_controller();


	//Run Power Path Controller Test once
	printk("\nEnd to End Test:  Power Path Controller\n");
	test_power_path_controller();

	printk("\nEnd to End Test:  Battery Monitor\n");
	test_battery_monitor();	


	//Run UI Test and stay in loop
	printk("\nEnd to End Test:  UI\n");
	test_ui_loop();
}



void test_end_to_end_manual(void)
{
	// /**
	//  * End-to-End Test 
	//  */

	// ADCReader_t ADCReader;
	// initADCReader(&ADCReader);

	// PWMController_t PWMController;
	// initPWMController(&PWMController);

	
	// UserInterface_t UserInterface;
	// initUserInterface(&UserInterface, &PWMController);

	// printk("End-to-End (Unit) Test:  Displays ADC readings of all channels, User Input controls the status LEDs as well as the PWM Brightness\n");
	// while(1){
	// 	clear_console();
	// 	//ADC
	// 	printk("ADC1: %5dmV     ", ADCReader.getADC1_mV(&ADCReader));
	// 	printk("ADC2: %5dmV     ", ADCReader.getADC2_mV(&ADCReader));
	// 	printk("V_BAT_ADC: %5dmV     ", ADCReader.getV_BAT_TEMP_ADC_mV(&ADCReader));
	// 	printk("V_BAT_TEMP_ADC: %5dmV     ", ADCReader.getV_BAT_ADC_mV(&ADCReader));
	// 	printk("BAT_CUR: %5dmV\n", ADCReader.getBAT_CUR_mV(&ADCReader));
		
	// 	//UI
	// 	uint32_t user_input = UserInterface.getUserInputLEDBrightnessPercent();
	// 	printk("User Input LED Brighness Percentage: %d \n", user_input);
	// 	UserInterface.setStatusLEDs(user_input);
		
	// 	//PWM
	// 	PWMController.setLEDBrightness(user_input);
	// 	printk("PWM Brightness: %d \n", PWMController.getLEDBrightnessPercentage());

	// 	k_sleep(K_MSEC(200));
	// }
}




void test_adc(void)
{
	/* ADC Reader Unit Tets*/
	ADCReader_t ADCReader;
	initADCReader(&ADCReader);

	printk("ADC1: %5dmV     ", ADCReader.getADC1_mV(&ADCReader));
	printk("ADC2: %5dmV     ", ADCReader.getADC2_mV(&ADCReader));
	printk("V_BAT_ADC: %5dmV     ", ADCReader.getV_BAT_ADC_mV(&ADCReader));
	printk("V_BAT_TEMP_ADC: %5dmV     ", ADCReader.getV_BAT_TEMP_ADC_mV(&ADCReader));
	printk("BAT_CUR: %5dmV\n", ADCReader.getBAT_CUR_mV(&ADCReader));

}

void test_adc_loop(void)
{
	while (1)
	{
		test_adc();
		k_msleep(100);
	}
}

void test_pwm_controller(void)
{
	/*PWM Controller Unit Test*/
	PWMController_t PWMController;
	initPWMController(&PWMController);


	printk("LED should fade on and off and brightness displayed on terminal.. \n");
		
	for(int i = 0;i < 10; i++)
	{
		PWMController.setLEDBrightness(i*10);
		printk("Brightness: %d \n", PWMController.getLEDBrightnessPercentage());
		k_sleep(K_MSEC(100));
	}
	for(int i = 0;i < 10; i++)
	{
		PWMController.setLEDBrightness(100-i*10);
		printk("Brightness: %d \n", PWMController.getLEDBrightnessPercentage());
		k_sleep(K_MSEC(100));
	}
}



void test_power_path_controller(void)
{
	// clear_console();
	/*Power Path Controller Unit Test*/

	GPIOController_t GPIOController;
	initGPIOController(&GPIOController);

	PowerPathController_t PowerPathController;
	initPowerPathController(&PowerPathController, &GPIOController);


	printk("Power Path Controller Test: check connected logic analyzer\n");

	printk("\n");


	printk("Turning Charging off for 2 seconds: PROG/PC12) should be high \n");
	PowerPathController.setBatteryCharger(false);
	k_sleep(K_MSEC(2000));
	printk("Turning Charging off: (PROG (PC12) should be low bec of 2K Pulldown\n");
	PowerPathController.setBatteryCharger(true);
	printk("\n");

	k_sleep(K_MSEC(500));

	printk("Turning Load On for 1 Second: EN2 (PC11) should be High).. \n");
	PowerPathController.setLoad(true);
	k_sleep(K_MSEC(1000));
	printk("Turning Load Off: EN2 (PC11) should be Low).. \n");
	PowerPathController.setLoad(false);
		
}



void test_ui_loop(void)
{
	/*User Interface Unit Test*/
	PWMController_t PWMController;
	initPWMController(&PWMController);

	GPIOController_t GPIOController;
	initGPIOController(&GPIOController);

	UserInterface_t UserInterface;
	initUserInterface(&UserInterface, &PWMController, &GPIOController);

	printk("User Interface Test: Displays user input and sets the status led \n");
	int soc_percentage = 0;

	int dir = 1;
	while(1){

		uint32_t user_input = UserInterface.getUserInputLEDBrightnessPercent();
		printk("User Input LED Brighness Percentage: %d \n", user_input);
		UserInterface.setStatusLEDs(soc_percentage);

		k_sleep(K_MSEC(500));
		if(dir)
		{
			soc_percentage = soc_percentage + 25;
		}
		else{
			soc_percentage = soc_percentage - 25;
		}

		if((soc_percentage == 100) | (soc_percentage == 0))
		{
			dir = !dir;
		}
	}
}

void test_battery_monitor(void)
{
	/* Battery Monitor Unit Test */
	ADCReader_t ADCReader;
	initADCReader(&ADCReader);

	GPIOController_t GPIOController;
	initGPIOController(&GPIOController);

	BatteryMonitor_t BatteryMonitor;
	initBatteryMonitor(&BatteryMonitor, &ADCReader, &GPIOController);

	printk("Battery Monitor Unit Test: \n");
	printk("%20s Temperature: %4d °C | Voltage: %4d mV | Current: %4d mA | Charging: %s\n","ADC_example: ",  1500,2100,1850,1 ? "true" : "false");
	printk("%20s Temperature: %4d °C | Voltage: %4d mV | Current: %4d mA | Charging: %s\n","Actual_example: ",  25,3900,300,1 ? "true" : "false");
	printk("\n");

	printk("%20s Temperature: %4d mV | Voltage: %4d mV | Current: %4d mV | Charging: %s\n","ADC: ",  BatteryMonitor.ADCReader->getV_BAT_TEMP_ADC_mV(BatteryMonitor.ADCReader),BatteryMonitor.ADCReader->getV_BAT_ADC_mV(BatteryMonitor.ADCReader),BatteryMonitor.ADCReader->getBAT_CUR_mV(BatteryMonitor.ADCReader),1 ? "true" : "false");
	printk("%20s Temperature: %4d °C | Voltage: %4d mV | Current: %4d mA | Charging: %s\n","Actual: ",  BatteryMonitor.getBatteryTemperature(),BatteryMonitor.getBatteryVoltage(),BatteryMonitor.getBatteryCurrent(), BatteryMonitor.getBatteryIsCharging() ? "true" : "false");
	printk("\n");


}
void test_battery_monitor_loop(void)
{
	/* Battery Monitor Unit Test */
	ADCReader_t ADCReader;
	initADCReader(&ADCReader);
	
	GPIOController_t GPIOController;
	initGPIOController(&GPIOController);

	BatteryMonitor_t BatteryMonitor;
	initBatteryMonitor(&BatteryMonitor, &ADCReader, &GPIOController);

	printk("Battery Monitor Unit Test: \n");
	printk("%20s Temperature: %4d °C | Voltage: %4d mV | Current: %4d mA | Charging: %s\n","ADC_example: ",  1500,2100,1850,1 ? "true" : "false");
	printk("%20s Temperature: %4d °C | Voltage: %4d mV | Current: %4d mA | Charging: %s\n","Actual_example: ",  25,3900,300,1 ? "true" : "false");
	printk("\n");

	while(1)
	{

		printk("%20s Temperature: %4d mV | Voltage: %4d mV | Current: %4d mV | Charging: %s\n","ADC: ",  BatteryMonitor.ADCReader->getV_BAT_TEMP_ADC_mV(BatteryMonitor.ADCReader),BatteryMonitor.ADCReader->getV_BAT_ADC_mV(BatteryMonitor.ADCReader),BatteryMonitor.ADCReader->getBAT_CUR_mV(BatteryMonitor.ADCReader),1 ? "true" : "false");
		printk("%20s Temperature: %4d °C | Voltage: %4d mV | Current: %4d mA | Charging: %s\n","Actual: ",  BatteryMonitor.getBatteryTemperature(),BatteryMonitor.getBatteryVoltage(),BatteryMonitor.getBatteryCurrent(), BatteryMonitor.getBatteryIsCharging() ? "true" : "false");
		printk("\n");
		k_msleep(1000);
	}



}




void clear_console(void)
{
	// printk("\n");
	// printk("\033[2J");
	// printk("\033[2J");
	// printk("\n\r");
}