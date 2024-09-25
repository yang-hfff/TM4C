#include "main.h"
#include "serial.h"

int main(void)
{  
    //�������
    FPUEnable();
    FPULazyStackingEnable();
    
    //����ϵͳʱ��40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    
    //���ô���
    uart_init(115200);
    
    //���
    printf("hello world\r\n");
    
    while(1)
    {
    }
}


