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





void main(void)
{



	/* For Testing ADC Reader*/
	ADCReader_t ADCReader;
	initADCReader(&ADCReader);
	while (1) {	
		printk("ADC1_mV: %dmV\n", ADCReader.getADC1_mV(&ADCReader));
		printk("ADC2_mV: %dmV\n", ADCReader.getADC2_mV(&ADCReader));
		printk("V_BAT_ADC_mV: %dmV\n", ADCReader.getV_BAT_TEMP_ADC_mV(&ADCReader));
		printk("V_BAT_TEMP_ADC_mV: %dmV\n", ADCReader.getV_BAT_ADC_mV(&ADCReader));
		printk("BAT_CUR_mV: %dmV\n", ADCReader.getBAT_CUR_mV(&ADCReader));
		k_sleep(K_MSEC(100));
	}

	/* For Teting User Input*/
	// while(1){

	// }
}
