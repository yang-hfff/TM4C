#include "main.h"
#include "PulWidModu.h"
#include "tick.h"


int main(void)
{  
    //�������
    FPUEnable();
    FPULazyStackingEnable();
    
    //����ϵͳʱ��40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    
    //��ʼ��PWM
    PWM_Init();
    
    while(1)
    {
        PWMPulseWidthSet(PWM0_BASE,PWM_OUT_1,45000);    //90%
        delay_ms(2000);
        PWMPulseWidthSet(PWM0_BASE,PWM_OUT_1,5000);     //10%
        delay_ms(2000);
    }
}


