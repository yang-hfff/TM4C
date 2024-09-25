#ifndef __TICK_H
#define __TICK_H


#include "main.h"


#define delay_ms(x) SysCtlDelay(x*(SysCtlClockGet()/3000))
#define delay_ns(x) SysCtlDelay(x*(SysCtlClockGet()/3000000))


extern uint32_t systime_ms;


void tick_init(void);


#endif /*__TICK_H*/



