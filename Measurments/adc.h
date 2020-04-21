
#ifndef ADC_H_
#define ADC_H_

#include <stddef.h>
#include "stm32f10x.h"

#define ADC_CHANNELS 6

uint16_t adc_value[ADC_CHANNELS];

void init_ADC();

#endif /* ADC_H_ */
