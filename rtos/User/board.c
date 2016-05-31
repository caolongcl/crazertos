#include "board.h"
#include "stdio.h"

/* 外部高速时钟初始化 */
/* HSE(8M) PLLCLK(72M) SYSCLK(72M) HCLK (to AHB) = SYSCLK /1
                                   PCLK1(to APB1)= SYSCLK /2          
                                   PCLK2(to APB2)= SYSCLK /1 */
uint8_t sys_clock_HSE(uint8_t pll)
{
	uint8_t temp=0;   
     /* 复位 并配置向量表 */
	RCC->APB1RSTR = 0x00000000;//复位结束			 
	RCC->APB2RSTR = 0x00000000; 
    RCC->AHBENR = 0x00000014;  //睡眠模式闪存和SRAM时钟使能.其他关闭.	  
    RCC->APB2ENR = 0x00000000; //外设时钟关闭.			   
    RCC->APB1ENR = 0x00000000;   
	RCC->CR |= 0x00000001;     //使能内部高速时钟HSION	 															 
	RCC->CFGR &= 0xF8FF0000;   //复位SW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]					 
	RCC->CR &= 0xFEF6FFFF;     //复位HSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     //复位HSEBYP	   	  
	RCC->CFGR &= 0xFF80FFFF;   //复位PLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE 
	RCC->CIR = 0x00000000;     //关闭所有中断		
    /*  */
 	RCC->CR|=1<<16;       //外部高速时钟使能HSEON
	while(!(RCC->CR>>17));//等待外部时钟就绪
	RCC->CFGR=0X00000400; //APB1=DIV2;APB2=DIV1;AHB=DIV1;   
	pll-=2;//抵消2个单位
	RCC->CFGR|=pll<<18;   //设置PLL值 2~16
	RCC->CFGR|=1<<16;	    //PLLSRC ON 
	FLASH->ACR|=0x32;	    //FLASH 2个延时周期
	RCC->CR|=0x01000000;  //PLLON
	while(!(RCC->CR>>25));//等待PLL锁定
	RCC->CFGR|=0x00000002;//PLL作为系统时钟	 
	while(temp!=0x02)     //等待PLL作为系统时钟设置成功
	{   
		temp=RCC->CFGR>>2;
		temp&=0x03;
	}   
    return ((pll+2)*8);  /* sys_clock */
}
/*------------------------------------------------------------*/

void power_on(void)     /* 等待初始化 */
{
    uint8_t i=0;       
    
    for(i=0;i<4;i++) {
        led_reflash(0x01);delay(900000);
        led_reflash(0x02);delay(900000);
        led_reflash(0x04);delay(900000);
        led_reflash(0x08);delay(900000);
    }
    for(i=0;i<3;i++) {
        led_reflash(0x0f);delay(900000);
        led_reflash(0x00);delay(900000);
    }
}
/*------------------------------------------------------------*/

void delay(uint32_t delay_time)  /* 粗略延时 */
{
   uint32_t i=0;
   
   for(i=0; i<delay_time; i++);
}

