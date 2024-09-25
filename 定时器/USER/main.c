#include "main.h"
#include "system.h"
#include "tim.h"


int main(void)
{  
    //�������
    FPUEnable();
    FPULazyStackingEnable();
    
    //����ϵͳʱ��40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    
    //��ʼ������
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    
    //��ʼ����ʱ��
    wTIM_Init(1000);
    
    while(1)
    {
        
    }
}


