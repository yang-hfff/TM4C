#include "key.h"
#include "main.h"
#include "system.h"
#include <stdio.h>



//定义两个按键
struct Button key1;
struct Button key2;



//按键读引脚函数接口
uint8_t read_button_pin(uint8_t button_id)
{
	switch(button_id)
	{
		case 1:return PF(4);
		case 2:return PF(0);
		default:return 0;
	}
}


//按键事件回调函数
void button_callback(void *parameter)
{
    struct Button *temp_button = (struct Button *)parameter;
    
    //触发来自哪个按键
    if(temp_button->button_id == 1)
    {
        //按键的什么事件触发
        switch(temp_button->event)
        {
            case SINGLE_CLICK: 
                printf("按键1单击\r\n");
                PF(1) = 1;
                PF(2) = 0;
                PF(3) = 0;
                break; 
            case DOUBLE_CLICK: 
                printf("按键1双击\r\n");
                PF(1) = 0;
                PF(2) = 1;
                PF(3) = 0;
                break; 
            case LONG_PRESS_START: 
                printf("按键1长按\r\n");
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
                printf("按键2单击\r\n");
                PF(1) = 0;
                PF(2) = 1;
                PF(3) = 1;
                break; 
            case DOUBLE_CLICK: 
                printf("按键2双击\r\n");
                PF(1) = 1;
                PF(2) = 0;
                PF(3) = 1;
                break; 
            case LONG_PRESS_START: 
                printf("按键2长按\r\n");
                PF(1) = 1;
                PF(2) = 1;
                PF(3) = 0;
                break; 
        }
    }
}


//按键初始化
void key_init(void)
{
    //开启时钟
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    
    //按键1
    GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
    
    //按键2
    GPIODirModeSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_DIR_MODE_IN);
    GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    
    //注册按键1
    button_init(&key1,read_button_pin,PRESS_LOW,1);
    button_attach(&key1, SINGLE_CLICK, button_callback);
    button_attach(&key1, DOUBLE_CLICK, button_callback);
    button_attach(&key1, LONG_PRESS_START, button_callback);
    button_start(&key1);
    
    //注册按键2
    button_init(&key2,read_button_pin,PRESS_LOW,2);
    button_attach(&key2, SINGLE_CLICK, button_callback);
    button_attach(&key2, DOUBLE_CLICK, button_callback);
    button_attach(&key2, LONG_PRESS_START, button_callback);
    button_start(&key2);
}




