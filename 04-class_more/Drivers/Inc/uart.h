#ifndef INC_UART_H_
#define INC_UART_H_

#include "stm32f411xx.h"
#include <stdio.h>

void uart_init(void);
int uart_write(int ch);
int uart_read(void);

#endif /* INC_UART_H_ */