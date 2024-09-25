#include "main.h"
#include "tick.h"
#include "system.h"
#include "serial.h"
#include "key.h"


int main(void)
{  
    //浮点加速
    FPUEnable();
    FPULazyStackingEnable();
    
    //设置系统时间40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    
    //初始化串口
    uart_init(115200);
    
    //初始化按键
    key_init();
    
    //初始化滴答定时器
    tick_init();
    
    //使能GPIO
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);    
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);  
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);  
    
    while(1)
    {
        //事件轮询放到了滴答定时器里面，5ms一次
        //所以写按键回调函数千万不能循环、延时、等待
        //sw2按键由于接到wakeup可能无法正常使用
        //sw1单击，双击，长按会有不同LED效果，并且会串口打印
    }
}


