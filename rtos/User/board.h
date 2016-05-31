#ifndef __BOARD_H__
#define __BOARD_H__

#include "stm32f10x.h"
#include "led.h"
#include "uart.h"
#include "motor.h"
#include "battery.h"

#define NVIC_VectTab_RAM             ((uint32_t)0x20000000)
#define NVIC_VectTab_FLASH           ((uint32_t)0x08000000)
#define AIRCR_VECTKEY_MASK           ((uint32_t)0x05FA0000)
#define NVIC_PriorityGroup_4         ((uint32_t)0x300) /*!< 4 bits for pre-emption priority
                                                            0 bits for subpriority */
#define SysTick_CLKSource_HCLK       ((uint32_t)0x00000004)

void power_on(void);
void delay(uint32_t delay_time);
uint8_t sys_clock_HSE(uint8_t pll);

#endif
