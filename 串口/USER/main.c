#include "main.h"
#include "serial.h"

int main(void)
{  
    //浮点加速
    FPUEnable();
    FPULazyStackingEnable();
    
    //设置系统时间40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    
    //配置串口
    uart_init(115200);
    
    //输出
    printf("hello world\r\n");
    
    while(1)
    {
    }
}


