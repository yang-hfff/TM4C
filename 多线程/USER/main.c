#include "main.h"
#include "system.h"
#include <rtthread.h>
#include "key.h"

struct rt_semaphore static_sem;

//LED线程
struct rt_thread led1_thread;
void led1_thread_entry(void* parameter)
{
    //使能GPIO
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
    while(1)
    {
        for(uint8_t i = 0;i < 8;i++)
        {
            PF(1) = !!(i&(0X01<<0));
            PF(2) = !!(i&(0X01<<1));
            PF(3) = !!(i&(0X01<<2));
            rt_thread_mdelay(500);
        }
    }
}
ALIGN(RT_ALIGN_SIZE)
rt_uint8_t rt_led1_thread_stack[256];


//打印线程
struct rt_thread echo_thread;
void echo_thread_entry(void* parameter)
{
    while(1)
    {
        rt_sem_take(&static_sem, RT_WAITING_FOREVER);
        rt_kprintf("等待按键（单击，双击，长按）：\r\n");
    }
}
ALIGN(RT_ALIGN_SIZE)
rt_uint8_t rt_echo_thread_stack[256];


//按键线程
struct rt_thread key_thread;
void key_thread_entry(void* parameter)
{
    while(1)
    {
        button_ticks();
        rt_thread_mdelay(5);
    }
}
ALIGN(RT_ALIGN_SIZE)
rt_uint8_t rt_key_thread_stack[256];

int main(void)
{  
    rt_sem_init(&static_sem,"ssem", 0, RT_IPC_FLAG_PRIO);
    
    rt_thread_init(&led1_thread,               
                    "led1",                      
                    led1_thread_entry,           
                    RT_NULL,                     
                    &rt_led1_thread_stack[0],    
                    sizeof(rt_led1_thread_stack), 
                    3,                           
                    20);                        
    rt_thread_startup(&led1_thread);

    rt_thread_init(&echo_thread,               
                    "echo",                      
                    echo_thread_entry,           
                    RT_NULL,                     
                    &rt_echo_thread_stack[0],    
                    sizeof(rt_echo_thread_stack), 
                    3,                           
                    20);                        
    rt_thread_startup(&echo_thread);
                    
    rt_thread_init(&key_thread,               
                    "key",                      
                    key_thread_entry,           
                    RT_NULL,                     
                    &rt_key_thread_stack[0],    
                    sizeof(rt_key_thread_stack), 
                    3,                           
                    20);                        
    rt_thread_startup(&key_thread);
                    
    return 0;
}


