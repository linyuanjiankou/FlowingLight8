#include "key.h"
#include "pre.h"
#include "stm32f1xx_hal.h"
#include <stdint.h>

tKeyEvent key_status = KEY_NONE;
tMode current_mode = MODE_PWM_OUTPUT;
tKeyEvent is_short_pressed = 0;
tKeyEvent is_long_pressed = 0;

void KEY_EXTI_Callback(uint16_t GPIO_PIN){
    if (GPIO_PIN == GPIO_PIN_3) {
        uint32_t last_time1 = HAL_GetTick();
        if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_RESET){
            while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3) == GPIO_PIN_RESET){
                uint32_t current_time1 = HAL_GetTick();
                uint32_t duration = current_time1 - last_time1;
            }
            if(duration >= 1000) {
                key_status = KEY_LONG;
                is_long_pressed = 1;
            }    
            else if(duration >= 300 && duration < 1000){
                key_status = KEY1_SHORT;
                is_short_pressed = 1;
            }
            else return;
        }else return;
    }
    else if (GPIO_PIN == GPIO_PIN_13){
        uint32_t last_time2 = HAL_GetTick();
        if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET){
            while(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET){
                uint32_t current_time2 = HAL_GetTick();
                uint32_t duration = current_time2 - last_time2;
            }
            if(duration >= 1000){
                key_status = KEY_LONG;
                is_long_pressed = 1;
            }
            else if(duration >= 300 && duration < 1000){
                key_status = KEY2_SHORT;
                is_short_pressed = 1;
            }
            else return;
        }else return;
    }
}

void KEY_ClearStatus(void){
    key_status = KEY_NONE;
}