#ifndef __TIM2_PWM_H__
#define __TIM2_PWM_H__

#include "stm32f1xx.h"

#ifdef __cplusplus
extern "C" {
#endif

void PWM_TIM2_Init(void);
void PWM_TIM2_Start(void);
void PWM_TIM2_Stop(void);
void PWM_TIM2_Setfreq(uint16_t freq);

#ifdef __cplusplus
}
#endif


#endif
