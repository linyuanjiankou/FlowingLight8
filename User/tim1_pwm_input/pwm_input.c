#include "pwm_input.h"
#include "tim.h"
#include "stm32f1xx_ll_tim.h"

#define PSC_HIGH 71
#define PSC_LOW 7199

static uint32_t freq = 0;
static uint8_t duty_100 = 0;

void PWM_Input_Init(void){
    HAL_TIM_IC_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_IC_Start(&htim1, TIM_CHANNEL_2);

    LL_TIM_EnableCounter(TIM1);
}

void PWM_Input_Measure(void){
    LL_TIM_SetPrescaler(TIM1, PSC_HIGH);
    LL_TIM_ClearFlag_UPDATE(TIM1);
    LL_TIM_ClearFlag_CC1(TIM1);
    LL_TIM_ClearFlag_CC2(TIM1);
    
    while (LL_TIM_IsActiveFlag_CC1(TIM1) == 0)
    {
        if (LL_TIM_IsActiveFlag_UPDATE(TIM1)) 
        {
            LL_TIM_SetPrescaler(TIM1, PSC_LOW);
            LL_TIM_ClearFlag_UPDATE(TIM1);
            LL_TIM_ClearFlag_CC1(TIM1);

            while (LL_TIM_IsActiveFlag_CC1(TIM1) == 0);
            
            uint16_t period = LL_TIM_IC_GetCaptureCH1(TIM1);
            uint16_t cc2 = LL_TIM_IC_GetCaptureCH2(TIM1);
            freq = 10000 / period;
            duty_100 = cc2 * 100 / period;
            return;
        }
        
    }
    
    uint16_t period = LL_TIM_IC_GetCaptureCH1(TIM1);
    uint16_t cc2 = LL_TIM_IC_GetCaptureCH2(TIM1);
    freq = 1000000 / period;
    duty_100 = cc2 * 100 / period;
}

uint32_t PWM_Input_GetFreq(void){
    return freq;
}

uint8_t PWM_Input_GetDuty(void){
    return duty_100;
}
