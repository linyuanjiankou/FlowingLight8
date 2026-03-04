#ifndef __ADC_POT_H__
#define __ADC_POT_H__

#include "stm32f1xx.h"

#ifdef __cplusplus
extern "C"{
#endif

void ADC_Pot_Start(void);
uint16_t ADC_Pot_Read(void);
uint16_t ADC_Pot_ReadFiltered(void);
void ADC_Pot_Stop(void);

#ifdef __cplusplus
}
#endif

#endif
