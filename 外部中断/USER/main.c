#include "main.h"
#include "system.h"
#include "tick.h"
#include "serial.h"
#include "exti.h"


int main(void)
{  
    //浮点加速
    FPUEnable();
    FPULazyStackingEnable();
    
    //设置系统时间40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    
    //LED对应GPIO初始化
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    
    //外部中断初始化
    EXTI_Init();
    
    while(1)
    {
    }
}


