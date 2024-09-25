#include "encoder.h"
#include "main.h"
#include "system.h"


//初始化编码器
void QEI_Init(void)
{
    const uint32_t MaxPos = 4000;
    
	//使能外设
	SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI0);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_QEI1);
	
    //使能复用的引脚
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
		
	// Unlock PD7
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
	HWREG(GPIO_PORTD_BASE + GPIO_O_CR)  |= 0x80;
	HWREG(GPIO_PORTD_BASE + GPIO_O_LOCK) = 0x00;
		
	// QEI1: PC5, PC6
	GPIOPinConfigure(GPIO_PC5_PHA1);
	GPIOPinTypeQEI(GPIO_PORTC_BASE , GPIO_PIN_5);
	GPIOPinConfigure(GPIO_PC6_PHB1);
	GPIOPinTypeQEI(GPIO_PORTC_BASE , GPIO_PIN_6);
	QEIConfigure(QEI1_BASE, (QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_RESET_IDX |QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP), MaxPos - 1);
	QEIVelocityConfigure(QEI1_BASE, QEI_VELDIV_1, SysCtlClockGet()/100);
	QEIVelocityEnable(QEI1_BASE);
	QEIEnable(QEI1_BASE);
    
	// QEI2: PD6, PD7
	GPIOPinConfigure(GPIO_PD6_PHA0);
	GPIOPinTypeQEI(GPIO_PORTD_BASE , GPIO_PIN_6);
	GPIOPinConfigure(GPIO_PD7_PHB0);
	GPIOPinTypeQEI(GPIO_PORTD_BASE , GPIO_PIN_7);
	QEIConfigure(QEI0_BASE, (QEI_CONFIG_CAPTURE_A_B | QEI_CONFIG_RESET_IDX |QEI_CONFIG_QUADRATURE | QEI_CONFIG_NO_SWAP), MaxPos - 1);
	QEIVelocityConfigure(QEI0_BASE, QEI_VELDIV_1, SysCtlClockGet()/100);
	QEIVelocityEnable(QEI0_BASE);
	QEIEnable(QEI0_BASE);
}






