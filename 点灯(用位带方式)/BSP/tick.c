#include "tick.h"


//��ſ���49.71�첻��ϼ�ʱ
uint32_t systime_ms = 0;


//ϵͳ�δ��ʼ��
void tick_init(void)
{
    //ϵͳʱ��40MHz������40k�ξ�������1msһ��tick
    SysTickPeriodSet(40000);
    SysTickIntEnable();
    SysTickEnable();
    IntMasterEnable();
}


//�жϷ�����
void SysTick_Handler(void)
{
    systime_ms++;
}



