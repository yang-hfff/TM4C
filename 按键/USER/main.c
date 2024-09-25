#include "main.h"
#include "tick.h"
#include "system.h"
#include "serial.h"
#include "key.h"


int main(void)
{  
    //�������
    FPUEnable();
    FPULazyStackingEnable();
    
    //����ϵͳʱ��40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    
    //��ʼ������
    uart_init(115200);
    
    //��ʼ������
    key_init();
    
    //��ʼ���δ�ʱ��
    tick_init();
    
    //ʹ��GPIO
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);    
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);  
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);  
    
    while(1)
    {
        //�¼���ѯ�ŵ��˵δ�ʱ�����棬5msһ��
        //����д�����ص�����ǧ����ѭ������ʱ���ȴ�
        //sw2�������ڽӵ�wakeup�����޷�����ʹ��
        //sw1������˫�����������в�ͬLEDЧ�������һᴮ�ڴ�ӡ
    }
}


