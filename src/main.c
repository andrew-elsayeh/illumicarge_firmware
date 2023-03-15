/*
 * Copyright (c) 2020 Libre Solar Technologies GmbH
 *
 * SPDX-License-Identifier: Apache-2.0
 */

// #include <inttypes.h>
// #include <stddef.h>
// #include <stdint.h>

// #include <zephyr/device.h>
// #include <zephyr/devicetree.h>
// #include <zephyr/drivers/adc.h>
// #include <zephyr/sys/printk.h>
// #include <zephyr/sys/util.h>

#include <zephyr/kernel.h>

#include "adc_reader/adc_reader.h"

#include "user_interface/user_interface.h"

#include "pwm_controller/pwm_controller.h"

void clear_console(void)
{
	printk("\n");
	printk("\033[2J");
	printk("\033[2J");
	printk("\n");
}

void main(void)
{
	// /**
	//  * End-to-End Test 
	//  */

	// ADCReader_t ADCReader;
	// initADCReader(&ADCReader);

	// UserInterface_t UserInterface;
	// initUserInterface(&UserInterface);

	// PWMController_t PWMController;
	// initPWMController(&PWMController);

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

	// /* ADC Reader Unit Tets*/
	// ADCReader_t ADCReader;
	// initADCReader(&ADCReader);
	// while (1) {	
	// 	printk("ADC1_mV: %dmV\n", ADCReader.getADC1_mV(&ADCReader));
	// 	printk("ADC2_mV: %dmV\n", ADCReader.getADC2_mV(&ADCReader));
	// 	printk("V_BAT_ADC_mV: %dmV\n", ADCReader.getV_BAT_TEMP_ADC_mV(&ADCReader));
	// 	printk("V_BAT_TEMP_ADC_mV: %dmV\n", ADCReader.getV_BAT_ADC_mV(&ADCReader));
	// 	printk("BAT_CUR_mV: %dmV\n", ADCReader.getBAT_CUR_mV(&ADCReader));
	// 	k_sleep(K_MSEC(100));
	// }

	// /*User Interface Integration Test*/
	// UserInterface_t UserInterface;
	// initUserInterface(&UserInterface);
	// printk("User Interface Test: Displays user input and sets the status led based percentage input \n");


	// while(1){

	// 	uint32_t user_input = UserInterface.getUserInputLEDBrightnessPercent();
	// 	printk("User Input LED Brighness Percentage: %d \n", user_input);
	// 	UserInterface.setStatusLEDs(user_input);

	// 	k_sleep(K_MSEC(20));
	// }


	// /*PWM Controller Unit Test*/
	// PWMController_t PWMController;
	// initPWMController(&PWMController);

	// printk("LED should fade on and off and brightness displayed on terminal.. \n");

	// while(1){
		
	// 	for(int i = 0;i < 100; i++)
	// 	{
	// 		PWMController.setLEDBrightness(i);
	// 		printk("Brightness: %d \n", PWMController.getLEDBrightnessPercentage());
	// 		k_sleep(K_MSEC(10));
	// 	}
	// 	for(int i = 0;i < 100; i++)
	// 	{
	// 		PWMController.setLEDBrightness(100-i);
	// 		printk("Brightness: %d \n", PWMController.getLEDBrightnessPercentage());
	// 		k_sleep(K_MSEC(10));
	// 	}
	// }


}
