#include "adc_reader.h"

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/adc.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/util.h>





enum adc_channels {
    ADC1_mV,
    ADC2_mV,
    V_BAT_TEMP_ADC_mV,
    V_BAT_ADC_mV,
    BAT_CUR_mV,
};

int32_t _adc_channels_mv[5];



void init_adc_reader(void);



#if !DT_NODE_EXISTS(DT_PATH(zephyr_user)) || \
	!DT_NODE_HAS_PROP(DT_PATH(zephyr_user), io_channels)
#error "No suitable devicetree overlay specified"
#endif

#define DT_SPEC_AND_COMMA(node_id, prop, idx) \
	ADC_DT_SPEC_GET_BY_IDX(node_id, idx),

/* Data of ADC io-channels specified in devicetree. */
static const struct adc_dt_spec adc_channels[] = {
	DT_FOREACH_PROP_ELEM(DT_PATH(zephyr_user), io_channels,
			     DT_SPEC_AND_COMMA)
};


int err;
uint16_t buf;
struct adc_sequence sequence = {
    .buffer = &buf,
    /* buffer size in bytes, not number of samples */
    .buffer_size = sizeof(buf),
};


void init_adc_reader(void)
{

    /* Configure channels individually prior to sampling. */
	for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) {
		if (!device_is_ready(adc_channels[i].dev)) {
			printk("ADC controller device not ready\n");
			return;
		}

		err = adc_channel_setup_dt(&adc_channels[i]);
		if (err < 0) {
			printk("Could not setup channel #%d (%d)\n", i, err);
			return;
		}
	}

}

// void readAndPrintAllChannels(void)
// {

//     // printk("ADC reading:\n");
//     for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) {
//         int32_t val_mv;

//         printk("- %s, channel %d: ",
//                 adc_channels[i].dev->name,
//                 adc_channels[i].channel_id);

//         (void)adc_sequence_init_dt(&adc_channels[i], &sequence);

//         err = adc_read(adc_channels[i].dev, &sequence);
//         if (err < 0) {
//             printk("Could not read (%d)\n", err);
//             continue;
//         } else {
//             printk("%"PRIu16, buf);
//         }

//         /* conversion to mV may not be supported, skip if not */
//         val_mv = buf;
//         err = adc_raw_to_millivolts_dt(&adc_channels[i],
//                             &val_mv);
//         if (err < 0) {
//             printk(" (value in mV not available)\n");
//         } else {
//             printk(" = %"PRId32" mV\n", val_mv);
//         }
//     }

// }


void updateReadings(void)
{

        for (size_t i = 0U; i < ARRAY_SIZE(adc_channels); i++) {
        int32_t val_mv;


        (void)adc_sequence_init_dt(&adc_channels[i], &sequence);

        err = adc_read(adc_channels[i].dev, &sequence);
        if (err < 0) {
            printk("Could not read (%d)\n", err);
            continue;
        } 

        val_mv = buf;
        err = adc_raw_to_millivolts_dt(&adc_channels[i],
                            &val_mv);
        if (err < 0) {
            printk(" (value in mV not available)\n");
        } else {
            _adc_channels_mv[i] = val_mv;
        }
    }


}

int32_t getADC1_mV(ADCReader_t *self)
{
    updateReadings();
    return _adc_channels_mv[ADC1_mV];
}
int32_t getADC2_mV(ADCReader_t *self)
{
    updateReadings();
    return _adc_channels_mv[ADC2_mV];
}
int32_t getV_BAT_ADC_mV(ADCReader_t *self)
{
    updateReadings();
    return _adc_channels_mv[V_BAT_ADC_mV];
}
int32_t getV_BAT_TEMP_ADC_mV(ADCReader_t *self)
{
    updateReadings();
    return _adc_channels_mv[V_BAT_TEMP_ADC_mV];
}
int32_t getBAT_CUR_mV(ADCReader_t *self)
{
    updateReadings();
    return _adc_channels_mv[BAT_CUR_mV];
}

uint8_t initADCReader(ADCReader_t *ADCReader)
{
    ADCReader->getADC1_mV = getADC1_mV;
    ADCReader->getADC2_mV = getADC2_mV;
    ADCReader->getV_BAT_ADC_mV = getV_BAT_ADC_mV;
    ADCReader->getV_BAT_TEMP_ADC_mV = getV_BAT_TEMP_ADC_mV;
    ADCReader->getBAT_CUR_mV = getBAT_CUR_mV;

    init_adc_reader();

    return 0;

}