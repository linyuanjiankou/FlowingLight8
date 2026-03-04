#include "mode.h"
uint8_t duty[3] = {10, 40, 100};

volatile uint8_t key_pressed = 0;
text1[6] = "Mode:"; //0,0
text2[6] = "Freq:"; //2,0
text3[6] = "Duty:"; //4,0
void MODE_PWM_OUTPUT_Run(uint16_t freq, uint32_t duty_num){
    if (is_long_pressed) is_long_pressed = 0;

    uint16_t now_freq = freq;
    uint32_t now_duty_num = duty_num;

    PWM_TIM2_Start();

    while(is_long_pressed == 0){
        float true_freq = (float *) freq / 10.0;
        PWM_TIM2_Setfreq(now_freq);
        PWM_TIM2_Setduty(duty[now_duty_num]);
        OLED_ShowString(0, 0, text1);
        OLED_ShowString(0, 40, current_mode);
        OLED_ShowString(2, 0, text2);
        OLED_ShowNum(2, 40, now_freq);
        OLED_ShowString(4, 0, text3);
        OLED_ShowNum(4, 40, duty[now_duty_num]);
        if(is_short_pressed){
            if(key_status == KEY1_SHORT) now_freq += 10;
            else if(key_status == KEY2_SHORT) now_duty_num++;
            is_short_pressed = 0;
            void KEY_ClearStatus();
        }
        Delay_ms(200);
        OLED_ShowString(2, 40, "    ");
        OLED_ShowString(4, 40, "    ");
    }

    PWM_TIM2_Stop();
    OLED_Clear();
    void KEY_ClearStatus();
}

void MODE_PWM_ADC(uint16_t freq){
    if (is_long_pressed) is_long_pressed = 0;

    PWM_TIM2_Start();

    while(is_long_pressed == 0){
        float true_freq = (float *) freq / 10.0;

        PWM_TIM2_Setfreq(freq);
        OLED_ShowString(0, 0, text1);
        OLED_ShowString(0, 40, current_mode);
        OLED_ShowString(2, 0, text2);
        OLED_ShowNum(2, 40, true_freq);

        Delay_ms(200);
        OLED_ShowString(2, 40, "    ");
    }

    PWM_TIM2_Stop();
    OLED_Clear();
    void KEY_ClearStatus();
}

void MODE_FLOWINGLIGHT_Run(){

}

void MODE_PWM_INPUT_Run(){

}