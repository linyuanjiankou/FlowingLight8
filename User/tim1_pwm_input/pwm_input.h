#ifndef __PWM_INPUT_H__
#define __PWM_INPUT_H__

#include "tim.h"

#ifdef __cplusplus
extern "C"{
#endif

void PWM_Input_Init(void);
void PWM_Input_Measure(void);
uint32_t PWM_Input_GetFreq(void);
uint8_t PWM_Input_GetDuty(void);

#ifdef __cplusplus
}
#endif

#endif
