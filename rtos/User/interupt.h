#ifndef __INTERUPT_H__
#define __INTERUPT_H__

#include "stm32f10x.h"

#define IT_Mask                   ((uint16_t)0x001F)  /*!< USART Interrupt Mask */
#define USART_IT_TXE              ((uint16_t)0x0727)
#define USART_IT_RXNE             ((uint16_t)0x0525)

void nvic_init(uint8_t NVIC_IRQChannel,uint8_t NVIC_IRQChannelPreemptionPriority,\
               uint8_t NVIC_IRQChannelSubPriority,FunctionalState NVIC_IRQChannelCmd);
ITStatus uart_get_it_status(USART_TypeDef* USARTx, uint16_t USART_IT);

#endif

