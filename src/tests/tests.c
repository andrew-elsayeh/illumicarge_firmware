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



#define ADC_TEST_DURATION 1000
#define BAT_TEST_DURATION 1000
void test_end_to_end(void)
{
	int64_t cur_time;
	
	GPIOController_t GPIOController;  
	ADCReader_t ADCReader;
	PWMController_t PWMController;
	PowerPathController_t PowerPathController;
	BatteryMonitor_t BatteryMonitor;
	UserInterface_t UserInterface;


	printk("\nEnd to End Test:  GPIO Controller\n");
	test_gpio_controller(&GPIOController);

	printk("\nEnd to End Test: ADC \n");
	cur_time = k_uptime_get(); 
	while(k_uptime_get() < cur_time + ADC_TEST_DURATION)
	{
		test_adc(&ADCReader);
		k_msleep(100);
	}

	//Run PWM Controller Test once
	printk("\nEnd to End Test:  PWM Controller\n");
	test_pwm_controller(&PWMController);


	//Run Power Path Controller Test once
	printk("\nEnd to End Test:  Power Path Controller\n");
	test_power_path_controller(&GPIOController, &PowerPathController);


	//Run Battery Monitor test for 1 Second
	printk("\nEnd to End Test:  Battery Monitor\n");
	cur_time = k_uptime_get(); 
	while(k_uptime_get() < cur_time + BAT_TEST_DURATION)
	{
		test_battery_monitor(&BatteryMonitor, &ADCReader, &GPIOController);	
		k_msleep(100);
	}


	//Run UI Test and stay in loop
	printk("\nEnd to End Test:  UI\n");
	test_ui_loop(&UserInterface, &GPIOController, &PWMController);
}


void mock_callback_function_1(void)
{
	printk("hello from mock_callback_function 1\n");
}
void mock_callback_function_2(void)
{
	printk("hello from mock_callback_function 2\n");
}
void test_gpio_controller(GPIOController_t *GPIOController)
{
	
	initGPIOController(GPIOController);

	printk("GPIO Controller Unit Test\n");
	printk("Turning all status LEDS off.. \n");
	GPIOController->setLED1(0);
	GPIOController->setLED2(0);
	GPIOController->setLED3(0);
	GPIOController->setLED4(0);
	k_msleep(500);

	printk("Turning all status LEDS on one by one.. \n");
	GPIOController->setLED1(1);
	k_msleep(250);
	GPIOController->setLED2(1);
	k_msleep(250);
	GPIOController->setLED3(1);
	k_msleep(250);
	GPIOController->setLED4(1);
	k_msleep(250);

	printk("Configuring button interrupts.. you have 5 seconds to test buttons \n");
	GPIOController->addBTN1Interrupt(mock_callback_function_1);
	GPIOController->addBTN2Interrupt(mock_callback_function_2);

	k_msleep(5000);

	printk("Switching button interrupts.. \n");
	GPIOController->addBTN1Interrupt(mock_callback_function_2);
	GPIOController->addBTN2Interrupt(mock_callback_function_1);
	
}


void test_adc(ADCReader_t *ADCReader)
{
	initADCReader(ADCReader);

	printk("ADC1: %5dmV     ", ADCReader->getADC1_mV(ADCReader));
	printk("ADC2: %5dmV     ", ADCReader->getADC2_mV(ADCReader));
	printk("V_BAT_ADC: %5dmV     ", ADCReader->getV_BAT_ADC_mV(ADCReader));
	printk("V_BAT_TEMP_ADC: %5dmV     ", ADCReader->getV_BAT_TEMP_ADC_mV(ADCReader));
	printk("BAT_CUR: %5dmV\n", ADCReader->getBAT_CUR_mV(ADCReader));

}

void test_adc_loop(ADCReader_t *ADCReader)
{
	while (1)
	{
		test_adc(ADCReader);
		k_msleep(100);
	}
}

void test_pwm_controller(PWMController_t *PWMController)
{
	/*PWM Controller Unit Test*/
	initPWMController(PWMController);


	printk("LED should fade on and off and brightness displayed on terminal.. \n");
		
	for(int i = 0;i < 10; i++)
	{
		PWMController->setLEDBrightness(i*10);
		printk("Brightness: %d \n", PWMController->getLEDBrightnessPercentage());
		k_sleep(K_MSEC(100));
	}
	for(int i = 0;i <= 10; i++)
	{
		PWMController->setLEDBrightness(100-i*10);
		printk("Brightness: %d \n", PWMController->getLEDBrightnessPercentage());
		k_sleep(K_MSEC(100));
	}
}



void test_power_path_controller(GPIOController_t *GPIOController, PowerPathController_t *PowerPathController)
{
	// clear_console();
	/*Power Path Controller Unit Test*/


	initPowerPathController(PowerPathController, GPIOController);


	printk("Power Path Controller Test: check connected logic analyzer\n");

	printk("\n");


	printk("Turning Charging off for 2 seconds: PROG/PC12) should be high \n");
	PowerPathController->setBatteryCharger(false);
	k_sleep(K_MSEC(2000));
	printk("Turning Charging off: (PROG (PC12) should be low bec of 2K Pulldown\n");
	PowerPathController->setBatteryCharger(true);
	printk("\n");

	k_sleep(K_MSEC(500));

	printk("Turning Load On for 1 Second: EN2 (PC11) should be High).. \n");
	PowerPathController->setLoad(true);
	k_sleep(K_MSEC(1000));
	printk("Turning Load Off: EN2 (PC11) should be Low).. \n");
	PowerPathController->setLoad(false);
		
}



void test_ui_loop(UserInterface_t *UserInterface, GPIOController_t *GPIOController, PWMController_t *PWMController)
{
	/*User Interface Unit Test*/
	initUserInterface(UserInterface, PWMController, GPIOController);

	printk("User Interface Test: Displays user input and sets the status led \n");
	int soc_percentage = 0;

	int dir = 1;
	while(1){

		uint32_t user_input = UserInterface->getUserInputLEDBrightnessPercent();
		printk("User Input LED Brighness Percentage: %d \n", user_input);
		UserInterface->setStatusLEDs(soc_percentage);

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

void test_battery_monitor(BatteryMonitor_t *BatteryMonitor, ADCReader_t *ADCReader, GPIOController_t *GPIOController)
{
	/* Battery Monitor Unit Test */

	initBatteryMonitor(BatteryMonitor, ADCReader, GPIOController);

	printk("Battery Monitor Unit Test: \n");
	printk("%20s Temperature: %4d °C | Voltage: %4d mV | Current: %4d mA | Charging: %s\n","ADC_example: ",  1500,2100,1850,1 ? "true" : "false");
	printk("%20s Temperature: %4d °C | Voltage: %4d mV | Current: %4d mA | Charging: %s\n","Actual_example: ",  25,3900,300,1 ? "true" : "false");
	printk("\n");

	printk("%20s Temperature: %4d mV | Voltage: %4d mV | Current: %4d mV | Charging: %s\n","ADC: ",  BatteryMonitor->ADCReader->getV_BAT_TEMP_ADC_mV(BatteryMonitor->ADCReader),BatteryMonitor->ADCReader->getV_BAT_ADC_mV(BatteryMonitor->ADCReader),BatteryMonitor->ADCReader->getBAT_CUR_mV(BatteryMonitor->ADCReader),1 ? "true" : "false");
	printk("%20s Temperature: %4d °C | Voltage: %4d mV | Current: %4d mA | Charging: %s\n","Actual: ",  BatteryMonitor->getBatteryTemperature(),BatteryMonitor->getBatteryVoltage(),BatteryMonitor->getBatteryCurrent(), BatteryMonitor->getBatteryIsCharging() ? "true" : "false");
	printk("\n");


}
void test_battery_monitor_loop(BatteryMonitor_t *BatteryMonitor, ADCReader_t *ADCReader, GPIOController_t *GPIOController)
{
	/* Battery Monitor Unit Test */
	initBatteryMonitor(BatteryMonitor, ADCReader, GPIOController);


	printk("Battery Monitor Unit Test: \n");
	printk("%20s Temperature: %4d °C | Voltage: %4d mV | Current: %4d mA | Charging: %s\n","ADC_example: ",  1500,2100,1850,1 ? "true" : "false");
	printk("%20s Temperature: %4d °C | Voltage: %4d mV | Current: %4d mA | Charging: %s\n","Actual_example: ",  25,3900,300,1 ? "true" : "false");
	printk("\n");

	while(1)
	{
		printk("%20s Temperature: %4d mV | Voltage: %4d mV | Current: %4d mV | Charging: %s\n","ADC: ",  BatteryMonitor->ADCReader->getV_BAT_TEMP_ADC_mV(BatteryMonitor->ADCReader),BatteryMonitor->ADCReader->getV_BAT_ADC_mV(BatteryMonitor->ADCReader),BatteryMonitor->ADCReader->getBAT_CUR_mV(BatteryMonitor->ADCReader),1 ? "true" : "false");
		printk("%20s Temperature: %4d °C | Voltage: %4d mV | Current: %4d mA | Charging: %s\n","Actual: ",  BatteryMonitor->getBatteryTemperature(),BatteryMonitor->getBatteryVoltage(),BatteryMonitor->getBatteryCurrent(), BatteryMonitor->getBatteryIsCharging() ? "true" : "false");
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