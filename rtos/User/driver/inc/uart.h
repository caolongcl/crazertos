#ifndef __UART_H__
#define __UART_H__

#include "stm32f10x.h"

#define USART_BUADRATE  115200

void uart1_init(uint32_t pclk2,uint32_t baudrate);

#endif
