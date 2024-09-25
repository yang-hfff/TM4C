#include "main.h"
#include "PulWidModu.h"
#include "tick.h"


int main(void)
{  
    //浮点加速
    FPUEnable();
    FPULazyStackingEnable();
    
    //设置系统时间40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    
    //初始化PWM
    PWM_Init();
    
    while(1)
    {
        PWMPulseWidthSet(PWM0_BASE,PWM_OUT_1,45000);    //90%
        delay_ms(2000);
        PWMPulseWidthSet(PWM0_BASE,PWM_OUT_1,5000);     //10%
        delay_ms(2000);
    }
}


