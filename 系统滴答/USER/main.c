#include "main.h"
#include "tick.h"
#include "system.h"
#include "serial.h"


int main(void)
{  
    //�졢ʱ���֡���
    int day,hour,minu,sec;
    
    //�������
    FPUEnable();
    FPULazyStackingEnable();
    
    //����ϵͳʱ��40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    
    //����ϵͳ�δ�
    tick_init();
    
    //��ʼ������
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


