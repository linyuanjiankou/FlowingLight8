#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f1xx.h"
#include "pre.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
    KEY_NONE = 0,
    KEY1_SHORT,
    KEY2_SHORT,
    KEY_LONG,
}tKeyEvent;

typedef enum{
    MODE_PWM_OUTPUT = 0,
    MODE_PWM_ADC,
    MODE_FLOWINGLIGHT,
    MODE_PWM_INPUT,
    MODE_MAX,
}tMode;

extern tMode current_mode;
extern tKeyEvent is_long_pressed;
extern tKeyEvent is_short_pressed; 
extern tKeyEvent key_status;

#define KEY1_PIN GPIO_PIN_3
#define KEY1_PORT GPIOB
#define KEY1_IRQn EXTI3_IRQn

#define KEY2_PIN GPIO_PIN_13
#define KEY2_PORT GPIOB
#define KEY2_IRQn EXTI15_10_IRQn

#ifdef __cplusplus
}
#endif

#endif