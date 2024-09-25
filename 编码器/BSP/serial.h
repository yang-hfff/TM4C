#ifndef __SERIAL_H
#define __SERIAL_H

#include "main.h"

void uart_init(uint32_t baud);
void uart_puts(char *str);
void uart_putchar(char str);
void uart_send(char *str);
void uart_write(void *addr,size_t byteNum);

#endif /*__SERIAL_H*/


