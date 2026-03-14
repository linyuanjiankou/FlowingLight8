#include "mode.h"
#include "adc_pot.h"
// #include "OLED.h"
#include "key.h"
#include "tim2_pwm.h"
#include "pre.h"
#include "stm32f1xx_ll_tim.h"

uint8_t ccr[3] = {1, 5, 9};

// const char text1[] = "Vol(mV):"; //4,0
// const char text2[] = "Freq(Hz):"; //2,0
// const char text3[] = "Duty(%):"; //4,0

void LED_Init(void){
    for(char i = 0; i < 8; i++){
        LED(i) = 0;
    }
}
void MODE_PWM_OUTPUT_Run(void){    
    uint16_t freq = 5;

    uint32_t current_time = HAL_GetTick();
    uint32_t last_time = 0;
    uint8_t num = 0;

    LED_Init();
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
        }

    }
    LL_TIM_SetAutoReload(TIM2,9); //arr = 10-1
    LL_TIM_OC_SetCompareCH1(TIM2, 1); //ccr = 1, duty = 10%
    PWM_TIM2_Stop();
    // OLED_Clear();

}

void MODE_PWM_LIGHT_Run(void){
    uint32_t current_time = HAL_GetTick();
    uint32_t last_time = 0;
    uint8_t num = 0;

    uint32_t ccr_num = 0;

    LED_Init();
    PWM_TIM2_Start();

    while (no_long_pressed){
		current_time = HAL_GetTick();
				
        if(current_time - last_time >=10){
            Key_Scan();
            last_time = current_time;
            num = (num + 1) % 20;
        }

        if(key[1].event == KEY_SHORT){
            ccr_num = (ccr_num + 1) % 3;
            key[1].event = KEY_NONE;
            LL_TIM_OC_SetCompareCH1(TIM2,ccr[ccr_num]);
            LL_TIM_GenerateEvent_UPDATE(TIM2);
        }
    }
	LL_TIM_SetAutoReload(TIM2,20000-1); // arr = 19999
    LL_TIM_OC_SetCompareCH1(TIM2, 9); //duty = 90%, ccr = 9
	PWM_TIM2_Stop();
}

void MODE_PWM_ADC_OUTPUT_Run(void){
    uint32_t current_time = HAL_GetTick();
    uint32_t last_time = 0;
    uint8_t num = 0;

    ADC_Pot_Start();
    uint16_t adc_value = ADC_Pot_ReadFiltered();
    // uint32_t Vol = ADC_Pot_GetVoltage_mV();
    uint16_t freq = (adc_value * 100) / 4095;
    PWM_TIM2_Setfreq(freq);
    PWM_TIM2_Start();

    while(no_long_pressed){
        current_time = HAL_GetTick();
        // float true_freq = (float) freq / 10.0f;
        adc_value = ADC_Pot_ReadFiltered();
        freq = (adc_value * 100) / 4095;
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
        if(current_time - last_time >= 10){
            Key_Scan();
            adc_value = ADC_Pot_ReadFiltered();
            last_time = current_time;
            num = (num + 1) % 20;
        }

    }
    PWM_TIM2_Stop();
    ADC_Pot_Stop();
    // OLED_Clear();
}

void PA0_SetGPIO(void){
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
}

void PA0_DefultGPIO(void){
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void MODE_FLOWINGLIGHT_Run(void){
    PWM_TIM2_Stop();
    PA0_SetGPIO();
    LED_Init();

    uint32_t current_time = HAL_GetTick();
    uint32_t key_last_time = HAL_GetTick();
    uint32_t led_last_time = HAL_GetTick();

    char light[] = {0,1,2,3,4,5,6,7};
    char direction = 0;
    char n = 0;

    uint16_t period[] = {200, 400, 800}; //单位：ms
    char i = 0;

    LED(light[n]) = 1;

    while(no_long_pressed){
        Delay_ms(1);
        current_time = HAL_GetTick();
        
        if((current_time - key_last_time) >= 10){
            Key_Scan();
            key_last_time = current_time;
        }

        if(key[0].event == KEY_SHORT){
            i = (i+1) % 3;
            key[0].event = KEY_NONE;
        }else if(key[1].event == KEY_SHORT){
            direction = !direction;
            key[1].event = KEY_NONE;
        }

        if((current_time - led_last_time) >= period[i]){
            led_last_time = current_time;
            LED(light[n]) = 0;
            char next = direction ? (n + 1) % 8 : (n + 7) % 8;
            LED(light[next]) = 1;
            n = next;
        }
    }
    PA0_DefultGPIO();
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
