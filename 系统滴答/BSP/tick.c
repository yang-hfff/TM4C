#include "tick.h"


//大概可以49.71天不间断计时
uint32_t systime_ms = 0;


//系统滴答初始化
void tick_init(void)
{
    //系统时钟40MHz，计数40k次就是周期1ms一次tick
    SysTickPeriodSet(40000);
    SysTickIntEnable();
    SysTickEnable();
    IntMasterEnable();
}


//中断服务函数
void SysTick_Handler(void)
{
    systime_ms++;
}



