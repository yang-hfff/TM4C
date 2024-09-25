#include "main.h"
#include "system.h"
#include "tick.h"
#include "serial.h"
#include "encoder.h"


int main(void)
{  
    int vl,vr,sl,sr;
    
    //浮点加速
    FPUEnable();
    FPULazyStackingEnable();
    
    //设置系统时间40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    
    //初始化串口
    uart_init(115200);
    
    //编码器初始化
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


