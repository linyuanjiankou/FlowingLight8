static uint32_t fac_us = 0;

/**
 * @brief 延时功能初始化函数
 * @note 该函数用于初始化系统滴答定时器，配置延时功能所需的参数
 *       获取系统时钟频率并计算每微秒对应的时钟周期数，存储在fac_us变量中
 * @param 无
 * @return 无
 */

void Delay_Init (void){

    uint32_t SystemCoreClock_Local = HAL_RCC_GetHCLKFreq();
    HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);
    fac_us = SystemCoreClock_Local / 1000000; //72

}

/**
 * @brief 微秒级延时函数
 * @param nus 需要延时的微秒数
 * @return 无
 * @details 使用SysTick定时器实现精确的微秒级延时
 */
void Delay_us (uint32_t nus) {

    uint32_t ticks;   // 目标时钟周期数
    uint32_t tlast;    // 上一次读取的计数值
    uint32_t tnow;    // 当前读取的计数值
    uint32_t tcnt = 0;  // 已累加的时钟周期数
    uint32_t reload;    // 重装载值

    // 计算需要等待的时钟周期数
    ticks = nus * fac_us;
    // 获取SysTick的重装载值
    reload = SysTick->LOAD;
    // 获取当前SysTick计数值作为起始值
    tlast = SysTick->VAL;
    // 循环检测已过的时钟周期是否达到目标值
    while (1) {
    tnow = SysTick->VAL;
    if (tnow > tlast) tcnt += reload - tnow + tlast;
    // 处理计数器翻转情况：从tlast到最大值再到tnow的周期数
    else tcnt += tlast - tnow;         // 正常情况：从tlast到tnow的周期数
    tlast = tnow;
    if (tcnt >= ticks) break;          // 达到目标延时时间，退出循环
    }

}
/**
 * @brief 毫秒级延时函数
 * @param nms 延时时间，单位为毫秒
 * @return 无
 */
void Delay_ms(uint32_t nms) {

    Delay_us(nms * 1000);
}