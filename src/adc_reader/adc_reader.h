#ifndef ADC_READER_H
#define ADC_READER_H

#include <inttypes.h>
#include <stddef.h>
#include <stdint.h>


typedef struct ADCReader ADCReader_t;

struct ADCReader {
    int32_t (*getADC1_mV) (ADCReader_t *self);
    int32_t (*getADC2_mV) (ADCReader_t *self);
    int32_t (*getV_BAT_ADC_mV) (ADCReader_t *self);
    int32_t (*getV_BAT_TEMP_ADC_mV) (ADCReader_t *self);
    int32_t (*getBAT_CUR_mV) (ADCReader_t *self);
};

uint8_t initADCReader(ADCReader_t *ADCReader);





// void readAndPrintAllChannels(void);
#endif /* ADC_READER_H */