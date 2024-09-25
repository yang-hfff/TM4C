#include "main.h"
#include "system.h"
#include "tick.h"
#include "serial.h"
#include "exti.h"


int main(void)
{  
    //�������
    FPUEnable();
    FPULazyStackingEnable();
    
    //����ϵͳʱ��40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    
    //LED��ӦGPIO��ʼ��
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    
    //�ⲿ�жϳ�ʼ��
    EXTI_Init();
    
    while(1)
    {
    }
}


