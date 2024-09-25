#include "main.h"
#include "system.h"
#include "tick.h"
#include "serial.h"


//pid�����ṹ��
struct 
{
    float p;
    float i;
    float d;
}pid;



int main(void)
{  
    //�������
    FPUEnable();
    FPULazyStackingEnable();
    
    //����ϵͳʱ��40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);
    
    //���ڳ�ʼ��
    uart_init(115200);
    
    //��ʼ��Ƭ��EEPROM
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0)){};
    if(EEPROMInit() != EEPROM_INIT_OK)
    {
        while(1){};
    }
    
    //ģ��Ӧ�ó���
#if 0
    //ģ���û�����������������ģʽ�����Ӱ����򴮿�����pid��������
    pid.p = 409.0f;
    pid.i = 0.0021f;
    pid.d = 0.37f;
    //�û�������������±���֮��
    EEPROMProgram((void *)&pid, 0x400, sizeof(pid));
    printf("pid save success\r\n");
#else   
    //ģ����������pid����
    EEPROMRead((void *)&pid, 0x400, sizeof(pid));
    printf("pid load success\r\n");
    printf("p=%f,i=%f,d=%f",pid.p,pid.i,pid.d);
#endif   
    while(1)
    {        
    }
}


