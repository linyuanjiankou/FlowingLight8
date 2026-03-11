#include "key.h"
#include "stm32f1xx_hal.h"
#include "pre.h"
#include <stdbool.h>

tKey key[2] = {
{
    .GPIOx = GPIOB,
    .pin = GPIO_PIN_3,
    .pressed_time = 0,
    .duration = 0,
    .state = KEY_Free,
    .event = KEY_NONE,
},{
    .GPIOx = GPIOB,
    .pin = GPIO_PIN_13,
    .pressed_time = 0,
    .duration = 0,
    .state = KEY_Free,
    .event = KEY_NONE,
}
};
void Key_Scan(void){
    for (uint8_t i = 0; i < 2; i++){
        bool key_pressed = HAL_GPIO_ReadPin(key[i].GPIOx, key[i].pin);

    switch(key[i].state){
        case KEY_Free:{
            if(!key_pressed){
                Delay_ms(10);
                if(HAL_GPIO_ReadPin(key[i].GPIOx, key[i].pin) == RESET){
                    key[i].state = KEY_Pressed;
                    key[i].pressed_time = HAL_GetTick();
                } 
            }else break;
            break;
        }
        case KEY_Pressed:{
            if(key_pressed){
                Delay_ms(10);
                if(HAL_GPIO_ReadPin(key[i].GPIOx, key[i].pin) == SET){
                    key[i].state = KEY_Released;
                    key[i].duration = HAL_GetTick() - key[i].pressed_time;
                }
            }else break;
            break;
        }
        case KEY_Released:{
            if(key[i].duration >= 1000){
                key[i].event = KEY_LONG;
                key[i].state = KEY_Processed;
            }else if(key[i].duration < 1000){
                key[i].event = KEY_SHORT;
                key[i].state = KEY_Processed;
            }
            break;
        }
        case KEY_Processed:{
            key[i].state = KEY_Free;
            break;
        }
        }
    }
}
