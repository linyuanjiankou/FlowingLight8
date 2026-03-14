#ifndef __MODE_H__
#define __MODE_H__

#ifdef __cplusplus
extern "C" {
#endif 

#include "key.h"

typedef enum{
    MODE_PWM_OUTPUT = 0,
    MODE_PWM_LIGHT,
    MODE_PWM_ADC,
    MODE_FLOWINGLIGHT,
    // MODE_PWM_INPUT,
    MODE_MAX,
}tMode;

extern tMode current_mode;

void LED_Init(void);
void MODE_PWM_OUTPUT_Run(void);
void MODE_PWM_LIGHT_Run(void);
void PA0_SetGPIO(void);
void PA0_DefultGPIO(void);
void MODE_PWM_ADC_OUTPUT_Run(void);
void MODE_FLOWINGLIGHT_Run(void);
// char* OLED_ShowMode(tMode current_mode);

#define no_long_pressed key[0].event != KEY_LONG && key[1].event != KEY_LONG


#ifdef __cplusplus
}
#endif

#endif
