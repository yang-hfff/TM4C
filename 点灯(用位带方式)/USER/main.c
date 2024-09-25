#include "main.h"
#include "system.h"
#include "tick.h"



int main(void)
{      
    //开启浮点加速
    FPUEnable();
    FPULazyStackingEnable();
    
    //配置系统时钟40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    
    //使能GPIO
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    while(1)
    {
        PF(1) = 1;
		delay_ms(500);
        PF(1) = 0;
		delay_ms(500);
    }
}


