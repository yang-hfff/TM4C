#include "PulWidModu.h"
#include "main.h"


//PWM初始化
void PWM_Init(void)
{
    //设置16分频，PWM时钟变成2.5MHz
    SysCtlPWMClockSet(SYSCTL_PWMDIV_16);
    
    //使能PWM0外设、使能GPIOB(输出端口)
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);  
 
	// 分配pwm信号
	GPIOPinTypePWM(GPIO_PORTB_BASE,GPIO_PIN_6); //PB6
	GPIOPinTypePWM(GPIO_PORTB_BASE,GPIO_PIN_7); //PB7
    
	// 使能引脚复用
	GPIOPinConfigure(GPIO_PB6_M0PWM0);																									
	GPIOPinConfigure(GPIO_PB7_M0PWM1);		   
        	
    //设置成向下计数模式
    PWMGenConfigure(PWM0_BASE,PWM_GEN_0,PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);  

    //设置周期T = 50000/2.5MHz = 20ms
    PWMGenPeriodSet(PWM0_BASE,PWM_GEN_0,50000);
    
    //脉宽设置
    PWMPulseWidthSet(PWM0_BASE,PWM_OUT_0,25000);    //50%
    PWMPulseWidthSet(PWM0_BASE,PWM_OUT_1,5000);     //10%
    
    //使能PWM输出
	PWMOutputState(PWM0_BASE,PWM_OUT_0_BIT,true);
	PWMOutputState(PWM0_BASE,PWM_OUT_1_BIT,true);
    
    //使能PWM
    PWMGenEnable(PWM0_BASE,PWM_GEN_0);
}





