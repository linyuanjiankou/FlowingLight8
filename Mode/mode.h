#ifndef __MODE_H__
#define __MODE_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "key.h"
#include "OLED.h"
#include "pre.h"
#include "pwm_input.h"
#include "tim2_pwm.h"

void MODE_PWM_OUTPUT_Run(uint16_t freq, uint32_t duty_num);
void MODE_PWM_ADC(uint16_t freq);
void MODE_FLOWINGLIGHT_Run();


#ifdef __cplusplus
}
#endif

#endif
