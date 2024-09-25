#include "main.h"
#include "tick.h"
#include "system.h"
#include "serial.h"


int main(void)
{  
    //天、时、分、秒
    int day,hour,minu,sec;
    
    //浮点加速
    FPUEnable();
    FPULazyStackingEnable();
    
    //设置系统时间40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    
    //开启系统滴答
    tick_init();
    
    //初始化串口
    uart_init(115200);
    while(1)
    {
        day = systime_ms/(24*60*60*1000);
        hour = (systime_ms/(60*60*1000))%24;
        minu = (systime_ms/(60*1000))%60;
        sec = (systime_ms/1000)%60;
        printf("%d:%d:%d:%d\r\n",day,hour,minu,sec);
        delay_ms(1000);
    }
}


