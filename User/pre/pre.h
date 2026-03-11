#ifndef __PRE_H__
#define __PRE_H__ 

#ifdef __cplusplus
extern "C" {
#endif 

#include <stdint.h>

void Delay_Init(void);
void Delay_us(uint32_t nus);
void Delay_ms(uint32_t nms);
	
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//IO口地址映射
#define GPIOA_ODR_Addr    (GPIOA_BASE+12) //0x4001080C 
#define GPIOB_ODR_Addr    (GPIOB_BASE+12) //0x40010C0C 

//IO口操作,只对单一的IO口!
//确保n的值小于16!
#define PAout(n)   BIT_ADDR(GPIOA_ODR_Addr,n)  //输出 
#define PBout(n)   BIT_ADDR(GPIOB_ODR_Addr,n)  //输出 

#define LED(n) PAout(n)

#ifdef __cplusplus
}
#endif

#endif
