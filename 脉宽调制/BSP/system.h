#ifndef __SYSTEM_H
#define __SYSTEM_H


#include <stdint.h>


#define SRAMB_BITBAND               0x20000000 
#define SRAMB_BITBANDALIAS          0x22000000


#define PERIPHERAL_BITBAND          0x40000000
#define PERIPHERAL_BITBANDALIAS     0x42000000


/*计算对应位带别名区地址值*/																	    
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
/*地址的数值类型转地址类型*/
#define MEM2ADDR(addr)  *((volatile unsigned long  *)(addr)) 
/*地址和位号寻址到位带别名区对应地址*/
#define BIT_ADDR(addr, bitnum)   MEM2ADDR(BITBAND(addr, bitnum)) 


#define GPIOA_DATA_ADDR                   (0x40004000UL + 255*sizeof(uint32_t))
#define GPIOB_DATA_ADDR                   (0x40005000UL + 255*sizeof(uint32_t))
#define GPIOC_DATA_ADDR                   (0x40006000UL + 255*sizeof(uint32_t))
#define GPIOD_DATA_ADDR                   (0x40007000UL + 255*sizeof(uint32_t))
#define GPIOE_DATA_ADDR                   (0x40024000UL + 255*sizeof(uint32_t))
#define GPIOF_DATA_ADDR                   (0x40025000UL + 255*sizeof(uint32_t))


#define PA(n)       BIT_ADDR(GPIOA_DATA_ADDR,n)  
#define PB(n)       BIT_ADDR(GPIOB_DATA_ADDR,n)  
#define PC(n)       BIT_ADDR(GPIOC_DATA_ADDR,n)  
#define PD(n)       BIT_ADDR(GPIOD_DATA_ADDR,n)  
#define PE(n)       BIT_ADDR(GPIOE_DATA_ADDR,n)  
#define PF(n)       BIT_ADDR(GPIOF_DATA_ADDR,n)  


#endif /*__SYSTEM_H*/



