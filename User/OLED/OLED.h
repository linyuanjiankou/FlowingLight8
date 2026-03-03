#ifndef _OLED_H_
#define _OLED_H_

#include "font.h"

#ifdef __cplusplus
extern "C"{
#endif

void OLED_WriteCmd(uint8_t cmd);
void OLED_WriteData(const uint8_t *data, uint16_t len);
void OLED_SetPos(uint8_t page, uint8_t col);
void OLED_Clear(void);
void OLED_Init(void);
void OLED_ShowChar(uint8_t page, uint8_t col, uint8_t chr);
void OLED_ShowString(uint8_t page, uint8_t col, char *str);
void OLED_ShowNum(uint8_t page, uint8_t col, uint32_t num);

#define OLED_WIDTH 128
#define OLED_HEIGHT 64
#define OLED_PAGES 8
#define OLED_ADDR 0x78


#ifdef __cplusplus
}
#endif


#endif
