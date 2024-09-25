#include "main.h"
#include "system.h"
#include "tick.h"



int main(void)
{      
    //�����������
    FPUEnable();
    FPULazyStackingEnable();
    
    //����ϵͳʱ��40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    
    //ʹ��GPIO
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


