void test_lib_function(void);


void init_adc_reader(void);

void readAndPrintAllChannels(void);

typedef struct ADCReader ADCReader_t;

struct ADCReader {

int32_t (*getADC1_mV) (ADCReader_t *self);
int32_t (*getADC2_mV) (ADCReader_t *self);
int32_t (*getV_BAT_ADC_mV) (ADCReader_t *self);
int32_t (*getV_BAT_TEMP_ADC_mV) (ADCReader_t *self);
int32_t (*getBAT_CUR_mV) (ADCReader_t *self);

};



uint8_t initADCReader(ADCReader_t *ADCReader);