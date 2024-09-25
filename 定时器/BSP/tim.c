#include "tim.h"
#include "main.h"
#include "system.h"



//32/64bit定时器初始化（采用级联）
//级联变成一个64位定时器
//拆分变成两个32位定时器
void wTIM_Init(uint64_t freq_hz)
{
    //开启定时器时钟
	SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);
    //设置不拆分并且周期计数
	TimerConfigure(WTIMER0_BASE, TIMER_CFG_PERIODIC_UP);
    //设置周期计数值
	TimerLoadSet64(WTIMER0_BASE, 40000000 / freq_hz - 1);
	// 级联的情况下默认都是设置定时器A
	TimerIntEnable(WTIMER0_BASE, TIMER_TIMA_TIMEOUT);
    //设置中断优先级
	IntPrioritySet(INT_WTIMER0A, 1);
	//中断使能
	IntEnable(INT_WTIMER0A);
    //使能总中断
	IntMasterEnable();
	//开启定时器
	TimerEnable(WTIMER0_BASE, TIMER_A);
}




//中断服务程序
void WTIMER0A_Handler()
{
	static uint32_t time_count = 0;
    
    uint32_t status = TimerIntStatus(WTIMER0_BASE,true);
	TimerIntClear(WTIMER0_BASE, status);
	
    if(time_count == 500)
	{
        PF(1) = !PF(1);
        time_count = 0;
    }
    else 
    {
        time_count++;
    }
}

