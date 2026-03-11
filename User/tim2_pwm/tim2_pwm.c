#include "tim2_pwm.h"
#include "tim.h"
#include "stm32f1xx_ll_tim.h"

static uint8_t duty = 10;

void PWM_TIM2_Init(void)
{
    LL_TIM_EnableARRPreload(TIM2);
    LL_TIM_OC_EnablePreload(TIM2, LL_TIM_CHANNEL_CH1);
}

void PWM_TIM2_Start(void)
{
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
}

void PWM_TIM2_Stop(void)
{
    HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_1);
}

void PWM_TIM2_Setfreq(uint16_t freq)
{
    if(freq < 5) freq = 5;
    if(freq > 100) freq = 100;

    uint32_t arr = 100000 / freq - 1;
    uint32_t ccr = (arr + 1) * duty / 100;

    LL_TIM_SetAutoReload(TIM2,arr);
    LL_TIM_OC_SetCompareCH1(TIM2,ccr);

    LL_TIM_GenerateEvent_UPDATE(TIM2);
}

void PWM_TIM2_Setduty(uint32_t duty_per)
{
    if(duty_per > 100) duty_per = 100;
    duty = duty_per;

    uint32_t arr = LL_TIM_GetAutoReload(TIM2);
    uint32_t ccr = duty * (arr + 1) / 100;

    LL_TIM_OC_SetCompareCH1(TIM2,ccr);

    LL_TIM_GenerateEvent_UPDATE(TIM2);
}
