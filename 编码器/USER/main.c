#include "main.h"
#include "system.h"
#include "tick.h"
#include "serial.h"
#include "encoder.h"


int main(void)
{  
    int vl,vr,sl,sr;
    
    //�������
    FPUEnable();
    FPULazyStackingEnable();
    
    //����ϵͳʱ��40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    
    //��ʼ������
    uart_init(115200);
    
    //��������ʼ��
    QEI_Init();
    
    while(1)
    {
        vl = QEIVelocityGet(QEI0_BASE)*QEIDirectionGet(QEI0_BASE);
        vr = QEIVelocityGet(QEI1_BASE)*QEIDirectionGet(QEI1_BASE);
        sl = QEIPositionGet(QEI0_BASE);
        sr = QEIPositionGet(QEI1_BASE);
        printf("%d\t%d\t%d\t%d\r\n",vl,vr,sl,sr);
    }
}


