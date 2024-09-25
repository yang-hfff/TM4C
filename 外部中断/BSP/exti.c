#include "exti.h"
#include "main.h"
#include "system.h"


//配置外部中断
void EXTI_Init(void)
{
	//使能外设
	SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF);
	//配置GPIOF_PIN_4为输入
	GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_DIR_MODE_IN);	
    //设置GPIOF_PIN_4为推挽上拉输出，驱动强度小点就可以
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	//设置为下降沿触发
	GPIOIntTypeSet( GPIO_PORTF_BASE,  GPIO_PIN_4, GPIO_FALLING_EDGE);
    //GPIO中断开启
	GPIOIntEnable( GPIO_PORTF_BASE,  GPIO_INT_PIN_4);
    //外部中断使能
    IntEnable(INT_GPIOF);
    //总中断使能
	IntMasterEnable();
}



//中断服务函数
void GPIOF_Handler(void)
{
	uint32_t GPIOF_IT_FLAG;

    GPIOF_IT_FLAG = GPIOIntStatus(GPIO_PORTF_BASE,true);
	GPIOIntClear(GPIO_PORTF_BASE, GPIO_INT_PIN_4);

	if((GPIOF_IT_FLAG & GPIO_PIN_4) == GPIO_PIN_4)
	{
        PF(1) = !PF(1);
	}
}




