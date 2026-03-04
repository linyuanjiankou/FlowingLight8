#include "OLED.h"
#include "font.h"
#include "i2c.h"
#include <stdio.h>
#include <string.h>

static char oled_buffer[129] = {0};

static uint8_t OLED_INIT_CMD[] = {
    0xAE,           // 关显示
    0xD5, 0x80,     // 设置时钟分频
    0xA8, 0x3F,     // 设置多路复用率(64行)
    0xD3, 0x00,     // 设置显示偏移
    0x40,           // 设置起始行
    0x8D, 0x14,     // 电荷泵使能
    0x20, 0x02,     // 设置页寻址模式
    0xA1,           // 段重映射
    0xC8,           // COM输出方向
    0xDA, 0x12,     // COM引脚配置
    0x81, 0xCF,     // 设置对比度
    0xD9, 0xF1,     // 预充电周期
    0xDB, 0x40,     // VCOMH电压
    0xA4,           // 正常显示
    0xA6,           // 非反显
    0xAF,           // 开显示
};

void OLED_WriteCmd(uint8_t cmd){
    uint8_t buf[2];
    buf[0] = 0x00;
    buf[1] = cmd;
    HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDR, buf, 2, 100);
}

void OLED_WriteData(const uint8_t *data, uint16_t len){
    oled_buffer[0] = 0x40;
    memcpy(&oled_buffer[1], data, len);
    HAL_I2C_Master_Transmit(&hi2c1, OLED_ADDR, (uint8_t *)oled_buffer, len+1, 100);
}

void OLED_SetPos(uint8_t page, uint8_t col){
    OLED_WriteCmd(0xB0 | page);
    OLED_WriteCmd(0x00 | (col & 0x0F));
    OLED_WriteCmd(0x10 | (col >> 4));
}

void OLED_Clear(void){
    uint8_t clear_buffer[128] = {0};
    for (uint8_t i = 0; i < OLED_PAGES; i++){
        OLED_SetPos(i,0);
        OLED_WriteData(clear_buffer, 128);
    }
}
void OLED_Init(void){
    HAL_Delay(100);
    for(uint8_t i = 0; i < sizeof(OLED_INIT_CMD); i++){
        OLED_WriteCmd(OLED_INIT_CMD[i]);
    }
    OLED_Clear();
}

void OLED_ShowChar(uint8_t page, uint8_t col, uint8_t chr){
    for(uint8_t i = 0; i < Font_Size; i++){
        if(FontUTF8[i].index[0] == chr){
            OLED_SetPos(page, col);
            OLED_WriteData(FontUTF8[i].data, 8);
            OLED_SetPos(page+1, col);
            OLED_WriteData(FontUTF8[i].data+8, 8);
            return;
        }
    }
}

void OLED_ShowString(uint8_t page, uint8_t col, char *str){
    while(*str != '\0'){
        OLED_ShowChar(page, col, *str);
        col += Font_Width;
        str++;
    }
}

void OLED_ShowNum(uint8_t page, uint8_t col, float num){
    snprintf(oled_buffer, sizeof(oled_buffer), "%.1f", num);
    OLED_ShowString(page, col, oled_buffer);
}