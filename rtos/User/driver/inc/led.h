#ifndef __LED_H__
#define __LED_H__

#include "stm32f10x.h"
#include "portmacro.h"

#define led_a_on    GPIOA->BSRR |= ((uint16_t)0x0800);
#define led_a_off   GPIOA->BRR  |= ((uint16_t)0x0800);


#define led_b_on    GPIOA->BSRR |= ((uint16_t)0x0100);
#define led_b_off   GPIOA->BRR  |= ((uint16_t)0x0100);


#define led_c_on    GPIOB->BSRR |= ((uint16_t)0x0002);
#define led_c_off   GPIOB->BRR  |= ((uint16_t)0x0002);


#define led_d_on    GPIOB->BSRR |= ((uint16_t)0x0008);
#define led_d_off   GPIOB->BRR  |= ((uint16_t)0x0008);

void led_init(void);
void led_reflash(uint8_t led_value);
void led_troggle( unsigned portBASE_TYPE uxLED);
void led_set( unsigned portBASE_TYPE uxLED,signed portBASE_TYPE xValue);

#endif

