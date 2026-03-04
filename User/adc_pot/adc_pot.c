#include "adc_pot.h"
#include "adc.h"

#define ADC_FILTER_SIZE 8

static uint16_t adc_buffer[ADC_FILTER_SIZE];
static uint8_t adc_index = 0;

void ADC_Pot_Start(void){
    HAL_ADC_Start(&hadc1);
}

void ADC_Pot_Stop(void){
    HAL_ADC_Stop(&hadc1);
}

uint16_t ADC_Pot_Read(void){
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    return HAL_ADC_GetValue(&hadc1);
}

uint16_t ADC_Pot_ReadFiltered(void){
    uint16_t raw = ADC_Pot_Read();

    adc_buffer[adc_index] = raw;
    adc_index = (adc_index + 1)%ADC_FILTER_SIZE;

    uint32_t sum = 0;
    for(uint8_t i = 0; i < ADC_FILTER_SIZE; i++){
        sum += adc_buffer[i];
    }
    return sum >> 3;
}
