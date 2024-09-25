#include "serial.h"


/*���������ģʽ*/
#pragma import(__use_no_semihosting)             

struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
 
/*����֧�ֺ���*/
void _sys_exit(int x) 
{ 
	x = x; 
} 


/*�ض���*/
int fputc(int ch, FILE *f)
{      
    UARTCharPut(UART0_BASE,ch);
	return ch;
}

//���ô���
void uart_init(uint32_t baud)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);   

    
    
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE,GPIO_PIN_0|GPIO_PIN_1);
    
    UARTConfigSetExpClk(UART0_BASE,SysCtlClockGet(),baud,(UART_CONFIG_WLEN_8|UART_CONFIG_STOP_ONE|UART_CONFIG_PAR_NONE));
    
    IntEnable(INT_UART0);  
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    IntMasterEnable();  
}


//�����ַ���(���س�����)
void uart_puts(char *str)
{
    while(*(str))
    {
        UARTCharPut(UART0_BASE,(uint8_t)(*(str++)));
    }
    UARTCharPut(UART0_BASE,(uint8_t)('\r'));
    UARTCharPut(UART0_BASE,(uint8_t)('\n'));
}


//�����ֽ�
void uart_putchar(char str)
{
    UARTCharPut(UART0_BASE,(uint8_t)str);
}


//�����ַ���(�����س�����)
void uart_send(char *str)
{
    while(*(str))
    {
        UARTCharPut(UART0_BASE,(uint8_t)(*(str++)));
    }
}


//����ָ����ַָ����С����
void uart_write(void *addr,size_t byteNum)
{
    uint8_t *data = addr;
    for(int i = 0;i < byteNum;i++)
    {
        UARTCharPut(UART0_BASE,data[i]); 
    }
}


//�жϷ�����
void UART0_Handler(void)
{
    uint32_t ui32Status;
    uint8_t temp;
    
    ui32Status = UARTIntStatus(UART0_BASE, true);
    UARTIntClear(UART0_BASE, ui32Status);

    while(UARTCharsAvail(UART0_BASE))
    {
        temp = UARTCharGetNonBlocking(UART0_BASE);
        UARTCharPutNonBlocking(UART0_BASE,temp);
    }
}


//���Ժ���֧��
void __error__(char *pcFilename, uint32_t ui32Line)
{
    printf("\r\n[error]%s,%d\r\n",pcFilename,ui32Line);
    while(1);
}



