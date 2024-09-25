#include "key.h"
#include "main.h"
#include "system.h"
#include <stdio.h>



//������������
struct Button key1;
struct Button key2;



//���������ź����ӿ�
uint8_t read_button_pin(uint8_t button_id)
{
	switch(button_id)
	{
		case 1:return PF(4);
		case 2:return PF(0);
		default:return 0;
	}
}


//�����¼��ص�����
void button_callback(void *parameter)
{
    struct Button *temp_button = (struct Button *)parameter;
    
    //���������ĸ�����
    if(temp_button->button_id == 1)
    {
        //������ʲô�¼�����
        switch(temp_button->event)
        {
            case SINGLE_CLICK: 
                printf("����1����\r\n");
                PF(1) = 1;
                PF(2) = 0;
                PF(3) = 0;
                break; 
            case DOUBLE_CLICK: 
                printf("����1˫��\r\n");
                PF(1) = 0;
                PF(2) = 1;
                PF(3) = 0;
                break; 
            case LONG_PRESS_START: 
                printf("����1����\r\n");
                PF(1) = 0;
                PF(2) = 0;
                PF(3) = 1;
                break; 
        }
    }
    else if(temp_button->button_id == 2)
    {
        switch(temp_button->event)
        {
            case SINGLE_CLICK: 
                printf("����2����\r\n");
                PF(1) = 0;
                PF(2) = 1;
                PF(3) = 1;
                break; 
            case DOUBLE_CLICK: 
                printf("����2˫��\r\n");
                PF(1) = 1;
                PF(2) = 0;
                PF(3) = 1;
                break; 
            case LONG_PRESS_START: 
                printf("����2����\r\n");
                PF(1) = 1;
                PF(2) = 1;
                PF(3) = 0;
                break; 
        }
    }
}


//������ʼ��
void key_init(void)
{
    //����ʱ��
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    
    //����1
    GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    
    //����2
    GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    
    //ע�ᰴ��1
    button_init(&key1,read_button_pin,PRESS_LOW,1);
    button_attach(&key1, SINGLE_CLICK, button_callback);
    button_attach(&key1, DOUBLE_CLICK, button_callback);
    button_attach(&key1, LONG_PRESS_START, button_callback);
    button_start(&key1);
    
    //ע�ᰴ��2
    button_init(&key2,read_button_pin,PRESS_LOW,2);
    button_attach(&key2, SINGLE_CLICK, button_callback);
    button_attach(&key2, DOUBLE_CLICK, button_callback);
    button_attach(&key2, LONG_PRESS_START, button_callback);
    button_start(&key2);
}




