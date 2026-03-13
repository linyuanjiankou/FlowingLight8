#ifndef __KEY_H__
#define __KEY_H__

#include "stm32f1xx.h"

#ifdef __cplusplus
extern "C" {
#endif

void Key_Scan(void);
void KEY_Clear(void);

typedef enum{
    KEY_Free = 0,
    KEY_Pressed,
    KEY_Released,
    KEY_Processed,
}tKeyState;

typedef enum{
    KEY_NONE = 0,
    KEY_SHORT,
    KEY_LONG,
}tKeyEvent;

typedef struct{
    GPIO_TypeDef *GPIOx;
    uint16_t pin;
    uint32_t pressed_time;
    uint32_t duration;
    tKeyState state;
    tKeyEvent event;
}tKey;

extern tKey key[2];

#ifdef __cplusplus
}
#endif

#endif
