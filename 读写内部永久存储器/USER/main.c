#include "main.h"
#include "system.h"
#include "tick.h"
#include "serial.h"


//pid参数结构体
struct 
{
    float p;
    float i;
    float d;
}pid;



int main(void)
{  
    //浮点加速
    FPUEnable();
    FPULazyStackingEnable();
    
    //设置系统时间40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    
    //串口初始化
    uart_init(115200);
    
    //初始化片内EEPROM
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0)){};
    if(EEPROMInit() != EEPROM_INIT_OK)
    {
        while(1){};
    }
    
    //模拟应用场景
#if 0
    //模拟用户长按按键加入设置模式，并从按键或串口设置pid参数过程
    pid.p = 409.0f;
    pid.i = 0.0021f;
    pid.d = 0.37f;
    //用户设置完参数按下保持之后
    EEPROMProgram((void *)&pid, 0x400, sizeof(pid));
    printf("pid save success\r\n");
#else   
    //模拟启动加载pid参数
    EEPROMRead((void *)&pid, 0x400, sizeof(pid));
    printf("pid load success\r\n");
    printf("p=%f,i=%f,d=%f",pid.p,pid.i,pid.d);
#endif   
    while(1)
    {        
    }
}


