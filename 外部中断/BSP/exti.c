#include "exti.h"
#include "main.h"
#include "system.h"


//�����ⲿ�ж�
void EXTI_Init(void)
{
	//ʹ������
	SysCtlPeripheralEnable( SYSCTL_PERIPH_GPIOF);
	//����GPIOF_PIN_4Ϊ����
	GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_DIR_MODE_IN);	
    //����GPIOF_PIN_4Ϊ�����������������ǿ��С��Ϳ���
	GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	//����Ϊ�½��ش���
	GPIOIntTypeSet( GPIO_PORTF_BASE,  GPIO_PIN_4, GPIO_FALLING_EDGE);
    //GPIO�жϿ���
	GPIOIntEnable( GPIO_PORTF_BASE,  GPIO_INT_PIN_4);
    //�ⲿ�ж�ʹ��
    IntEnable(INT_GPIOF);
    //���ж�ʹ��
	IntMasterEnable();
}



//�жϷ�����
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




