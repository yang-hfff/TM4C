#include "main.h"
#include "system.h"
#include "tick.h"
#include "serial.h"


int main(void)
{  
    //�������
    FPUEnable();
    FPULazyStackingEnable();
    
    //����ϵͳʱ��40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    
    while(1)
    {
        
    }
}


