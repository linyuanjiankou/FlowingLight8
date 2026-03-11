#include "mode.h"
#include "adc_pot.h"
// #include "OLED.h"
#include "key.h"
#include "tim2_pwm.h"
#include "pre.h"

uint8_t duty[3] = {10, 40, 90};

// const char text1[] = "Vol(mV):"; //4,0
// const char text2[] = "Freq(Hz):"; //2,0
// const char text3[] = "Duty(%):"; //4,0
void MODE_PWM_OUTPUT_Run(void){    
    uint16_t freq = 5;
    uint32_t duty_num = 0;

    uint32_t current_time = HAL_GetTick();
    uint32_t last_time = 0;
    uint8_t num = 0;

    PWM_TIM2_Start();
    while (no_long_pressed) {
        current_time = HAL_GetTick();        
        // if(num == 0){
        //     float true_freq = (float) freq / 10.0f;


        //     OLED_ShowString(2, 72, "    ");
        //     OLED_ShowString(4, 64, "    ");
        //     char *mode = OLED_ShowMode(current_mode);
        //     OLED_ShowString(0, 0, mode);
        //     OLED_ShowString(2, 0, text2);
        //     OLED_ShowNum(2, 72, true_freq);
        //     OLED_ShowString(4, 0, text3);
        //     OLED_ShowNum(4, 64, duty[duty_num]);
        // }
        if(current_time - last_time >=10){
            Key_Scan();
            last_time = current_time;
            num = (num + 1) % 20;
        }
        if(key[0].event == KEY_SHORT){
            freq += 5;
            if(freq > 100){freq = 5;}
            key[0].event = KEY_NONE;
            PWM_TIM2_Setfreq(freq);
        }else if(key[1].event == KEY_SHORT){
            duty_num = (duty_num + 1) % 3;
            key[1].event = KEY_NONE;
            PWM_TIM2_Setduty(duty[duty_num]);
        }

    }
    PWM_TIM2_Stop();
    // OLED_Clear();

}

void MODE_PWM_ADC_OUTPUT_Run(void){
    uint32_t current_time = HAL_GetTick();
    uint32_t last_time = 0;
    uint8_t num = 0;

    uint16_t adc_value = ADC_Pot_ReadFiltered();
    uint32_t Vol = ADC_Pot_GetVoltage_mV();
    uint16_t freq = (adc_value * 100) / 4095;

    PWM_TIM2_Start();

    while(no_long_pressed){
        current_time = HAL_GetTick();
        // float true_freq = (float) freq / 10.0f;
        PWM_TIM2_Setfreq(freq);
        // if(num == 0){
            
        //     char *mode = OLED_ShowMode(current_mode);
        //     OLED_ShowString(0, 0, mode);
        //     OLED_ShowString(2, 0, text2);
        //     OLED_ShowString(2, 72, "    ");
        //     OLED_ShowNum(2, 72, true_freq);
        //     OLED_ShowString(4, 0, text1);
        //     OLED_ShowNum(4, 64, Vol);
        // }
        if(current_time - last_time >=10){
            adc_value = ADC_Pot_ReadFiltered();
            last_time = current_time;
            num = (num + 1) % 20;
        }

    }
    PWM_TIM2_Stop();
    // OLED_Clear();
}
void MODE_FLOWINGLIGHT_Run(void){
    uint8_t light[8] = {0,1,2,3,4,5,6,7};
    uint16_t period[3] = {50,200,400};
    uint8_t n = 0;
    uint8_t i = 0;
    uint8_t direction = 0;

    uint32_t current_time = HAL_GetTick();
    uint32_t last_time = 0;
    uint16_t num = 0;

    while(no_long_pressed){
        current_time = HAL_GetTick();
        // if((num % 20) == 0){
        //     char *mode = OLED_ShowMode(current_mode);
        //     OLED_ShowString(0, 0, mode);
        //     num++;
        // }

        if((num % (period[i] / 10)) == 0){
            if(direction){
                LED(light[n]) = 1;
                LED(light[(n + 7) % 8]) = 0;
                n = (n+1) % 8;
            }
            else{
                LED(light[n]) = 1;
                LED(light[(n + 1) % 8]) = 0;
                n = (n+1) % 8;
            }
        }
        if(current_time - last_time >=10){
        Key_Scan();
        last_time = current_time;
        num += 1;
        }

        if(key[0].event == KEY_SHORT){
            i = (i + 1) % 3;
            key[0].event = KEY_NONE;
        }
        else if(key[1].event == KEY_SHORT){
            direction = !direction;
            key[1].event = KEY_NONE;
        }
    }
}

// char* OLED_ShowMode(tMode current_mode) {
//     switch (current_mode) {
//         case MODE_PWM_OUTPUT:
//             return "Mode:General";

//         case MODE_PWM_ADC:
//             return "Mode:ADC";

//         case MODE_FLOWINGLIGHT:
//             return "Mode:Flow";

//         case MODE_MAX:
// 			break;
//     }
// 		return "Mode:Err";
// }
// void MODE_PWM_INPUT_Run(){
//     if(is_long_pressed) is_long_pressed = 0;

//     PWM_Input_Init();
// }
