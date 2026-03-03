#include <stdint.h>
#include "pre.h"


static uint32_t fac_us = 0;

/**
 * @brief 初始化延时功能相关的系统配置。
 * 
 * 该函数用于初始化系统滴答定时器（SysTick）的时钟源，并计算微秒级延时因子。
 * 通过获取系统核心时钟频率，配置SysTick时钟源为HCLK，并计算每微秒对应的计数值。
 * 
 * @param 无
 * @return 无
 */
void Delay_Init (void){

    // 获取系统核心时钟频率（HCLK）
    uint32_t SystemCoreClock_Local = HAL_RCC_GetHCLKFreq();

    // 配置SysTick时钟源为HCLK
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

    // 计算每微秒对应的计数值，用于后续延时函数
    fac_us = SystemCoreClock_Local / 1000000; //72

}

/**
 * @brief 延时函数，以微秒为单位进行延时
 * 
 * 该函数通过读取SysTick定时器的计数值来实现精确的微秒级延时。
 * 利用SysTick定时器的自动重载特性，计算经过的时间并累加，
 * 直到达到指定的延时时间。
 * 
 * @param nus 需要延时的微秒数（uint32_t类型）
 * 
 * @note 该函数依赖于全局变量 `fac_us` 和SysTick定时器的配置。
 *       `fac_us` 表示每微秒对应的SysTick计数周期数。
 *       SysTick定时器需在调用此函数前正确初始化。
 */
void Delay_us (uint32_t nus) {
    uint32_t ticks;      // 总共需要等待的SysTick计数周期数
    uint32_t tlast;      // 上一次读取的SysTick计数值
    uint32_t tnow;       // 当前读取的SysTick计数值
    uint32_t tcnt = 0;   // 已累计的SysTick计数周期数
    uint32_t reload;     // SysTick定时器的重载值

    // 计算总共需要等待的SysTick计数周期数
    ticks = nus * fac_us;

    // 获取SysTick定时器的重载值和初始计数值
    reload = SysTick->LOAD;
    tlast = SysTick->VAL;

    // 循环读取SysTick计数值并累加，直到达到目标延时
    while (1) {
        tnow = SysTick->VAL;

        // 处理SysTick计数器溢出的情况（从0回到重载值）
        if (tnow > tlast) 
            tcnt += reload - tnow + tlast;
        else 
            tcnt += tlast - tnow;

        tlast = tnow;

        // 如果累计计数达到或超过目标值，则退出循环
        if (tcnt >= ticks) 
            break;
    }
}
/**
 * @brief 延时函数，以毫秒为单位进行延时。
 *
 * 该函数通过调用 Delay_us 函数实现毫秒级延时。将输入的毫秒数转换为微秒数，
 * 然后传递给 Delay_us 函数执行实际的延时操作。
 *
 * @param nms 需要延时的毫秒数，类型为 uint32_t。
 */
void Delay_ms(uint32_t nms) {

    Delay_us(nms * 1000);
}