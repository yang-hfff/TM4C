#include "main.h"
#include "system.h"
#include "serial.h"
#include <rtthread.h>

//流水灯线程
struct rt_thread led_tcb;
void led_thread_entry(void *parameter)
{
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    while(1)
    {
        PF(1) = 1;
		rt_thread_mdelay(500);
        PF(1) = 0;
		rt_thread_mdelay(500);
    }
}
ALIGN(RT_ALIGN_SIZE)
rt_uint8_t led_stack[256];

//主函数
int main(void)
{  
    rt_thread_init(&led_tcb,
                    "led",
                    led_thread_entry,
                    RT_NULL,
                    led_stack,
                    sizeof(led_stack),
                    3,
                    20);
    rt_thread_startup(&led_tcb);
}


//清空屏幕命令行
int clear(int argc,char *argv[])
{
    rt_kprintf("\033c");
    return 0;
}
MSH_CMD_EXPORT(clear,clear the sccream);


//字体颜色命令行
int color(int argc,char *argv[])
{
    const static char ANSI_COLOR_RED[] = "\x1b[31m";
    const static char ANSI_COLOR_GREEN[] = "\x1b[32m";
    const static char ANSI_COLOR_YELLOW[] = "\x1b[33m";
    const static char ANSI_COLOR_BLUE[] = "\x1b[34m";
    const static char ANSI_COLOR_MAGENTA[] = "\x1b[35m";
    const static char ANSI_COLOR_CYAN[] = "\x1b[36m";
    const static char ANSI_COLOR_RESET[] = "\x1b[0m";
    
    if(argc != 2)
    {
        rt_kprintf("ussage\n");
        rt_kprintf("color [param]\n");
        rt_kprintf("param as follows:\n");
        rt_kprintf("\tred\n");
        rt_kprintf("\tgreen\n");
        rt_kprintf("\tyellow\n");
        rt_kprintf("\tblue\n");
        rt_kprintf("\tmagenta\n");
        rt_kprintf("\tcyan\n");
        rt_kprintf("\treset\n");
    }
    else 
    {
        if(rt_strcmp(argv[1],"red") == 0)
        {
            rt_kprintf(ANSI_COLOR_RED);
        }
        else if(rt_strcmp(argv[1],"green") == 0)
        {
            rt_kprintf(ANSI_COLOR_GREEN);
        }
        else if(rt_strcmp(argv[1],"yellow") == 0)
        {
            rt_kprintf(ANSI_COLOR_YELLOW);
        }
        else if(rt_strcmp(argv[1],"blue") == 0)
        {
            rt_kprintf(ANSI_COLOR_BLUE);
        }
        else if(rt_strcmp(argv[1],"magenta") == 0)
        {
            rt_kprintf(ANSI_COLOR_MAGENTA);
        }
        else if(rt_strcmp(argv[1],"cyan") == 0)
        {
            rt_kprintf(ANSI_COLOR_CYAN);
        }
        else if(rt_strcmp(argv[1],"reset") == 0)
        {
            rt_kprintf(ANSI_COLOR_RESET);
        }
        else 
        {
            rt_kprintf("param error\n");          
        }
    }
    return 0;
}
MSH_CMD_EXPORT(color,change the console character color);



//EEPROM查看
int eeprom(int argc,char *argv[])
{
    if(argc == 2)
    {
        if(rt_strcmp(argv[1],"init") == 0)
        {
            SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
            while(!SysCtlPeripheralReady(SYSCTL_PERIPH_EEPROM0)){};
            if(EEPROMInit() != EEPROM_INIT_OK)
            {
                rt_kprintf("eeprom init fail\n");
                while(1){};
            }
            else 
            {
                rt_kprintf("eeprom init success\n");
            }
        }
        else if(rt_strcmp(argv[1],"look") == 0)
        {
            uint8_t *arr = (uint8_t *)rt_malloc(2048*sizeof(uint8_t));
            EEPROMRead((void *)arr,0X00,2048*sizeof(uint8_t));
            rt_kprintf("offset");
            for(int i = 0;i < 16;i++)
            {
                rt_kprintf(" %02x ",i);
            }
            rt_kprintf("\n");
            for(int i = 0;i < 2048;i++)
            {
                if(i % 16 == 0)
                {
                    rt_kprintf("\n");
                    rt_kprintf("%04x: ",i);
                }
                rt_kprintf(" %02x ",arr[i]);
            }
            rt_kprintf("\n");
            rt_free(arr);
        }
        else 
        {
            rt_kprintf("param error\n");
        }
    }
    else if(argc == 3)
    {
        rt_kprintf("%s,%d:no complete!!!\n",__FILE__,__LINE__);
    }
    else 
    {
        rt_kprintf("ussage\n");
        rt_kprintf("eeprom [param1]\n");
        rt_kprintf("eeprom look [param2]\n");
        rt_kprintf("param1 as follows:\n");
        rt_kprintf("\tinit\n");
        rt_kprintf("\tlook\n");
        rt_kprintf("param2 is addr of eeprom unit you want to look\n");
    }
    return 0;
}
MSH_CMD_EXPORT(eeprom,look eeprom reflect);




