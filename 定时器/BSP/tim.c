#include "tim.h"
#include "main.h"
#include "system.h"



//32/64bit��ʱ����ʼ�������ü�����
//�������һ��64λ��ʱ��
//��ֱ������32λ��ʱ��
void wTIM_Init(uint64_t freq_hz)
{
    //������ʱ��ʱ��
	SysCtlPeripheralEnable(SYSCTL_PERIPH_WTIMER0);
    //���ò���ֲ������ڼ���
	TimerConfigure(WTIMER0_BASE, TIMER_CFG_PERIODIC_UP);
    //�������ڼ���ֵ
	TimerLoadSet64(WTIMER0_BASE, 40000000 / freq_hz - 1);
	// �����������Ĭ�϶������ö�ʱ��A
	TimerIntEnable(WTIMER0_BASE, TIMER_TIMA_TIMEOUT);
    //�����ж����ȼ�
	IntPrioritySet(INT_WTIMER0A, 1);
	//�ж�ʹ��
	IntEnable(INT_WTIMER0A);
    //ʹ�����ж�
	IntMasterEnable();
	//������ʱ��
	TimerEnable(WTIMER0_BASE, TIMER_A);
}




//�жϷ������
void WTIMER0A_Handler()
{
	static uint32_t time_count = 0;
    
    uint32_t status = TimerIntStatus(WTIMER0_BASE,true);
	TimerIntClear(WTIMER0_BASE, status);
	
    if(time_count == 500)
	{
        PF(1) = !PF(1);
        time_count = 0;
    }
    else 
    {
        time_count++;
    }
}

