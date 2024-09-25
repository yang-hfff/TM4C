#include "PulWidModu.h"
#include "main.h"


//PWM��ʼ��
void PWM_Init(void)
{
    //����16��Ƶ��PWMʱ�ӱ��2.5MHz
    SysCtlPWMClockSet(SYSCTL_PWMDIV_16);
    
    //ʹ��PWM0���衢ʹ��GPIOB(����˿�)
	SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);  
 
	// ����pwm�ź�
	GPIOPinTypePWM(GPIO_PORTB_BASE,GPIO_PIN_6); //PB6
	GPIOPinTypePWM(GPIO_PORTB_BASE,GPIO_PIN_7); //PB7
    
	// ʹ�����Ÿ���
	GPIOPinConfigure(GPIO_PB6_M0PWM0);																									
	GPIOPinConfigure(GPIO_PB7_M0PWM1);		   
        	
    //���ó����¼���ģʽ
    PWMGenConfigure(PWM0_BASE,PWM_GEN_0,PWM_GEN_MODE_DOWN|PWM_GEN_MODE_NO_SYNC);  

    //��������T = 50000/2.5MHz = 20ms
    PWMGenPeriodSet(PWM0_BASE,PWM_GEN_0,50000);
    
    //��������
    PWMPulseWidthSet(PWM0_BASE,PWM_OUT_0,25000);    //50%
    PWMPulseWidthSet(PWM0_BASE,PWM_OUT_1,5000);     //10%
    
    //ʹ��PWM���
	PWMOutputState(PWM0_BASE,PWM_OUT_0_BIT,true);
	PWMOutputState(PWM0_BASE,PWM_OUT_1_BIT,true);
    
    //ʹ��PWM
    PWMGenEnable(PWM0_BASE,PWM_GEN_0);
}





