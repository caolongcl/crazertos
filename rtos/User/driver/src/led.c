#include "led.h"

/* led init */
void led_init(void)
{
    RCC->APB2ENR|=1<<2;     //GPIOA
    RCC->APB2ENR|=1<<3;     //GPIOB

    RCC->APB2ENR|=1<<0;      //使能复用时钟
    GPIOB->CRL&=0XFFFF0F0F;  //PB1,3 推挽输出
    GPIOB->CRL|=0X00003030;
    GPIOB->ODR|=5<<1;        //PB1,3 上拉

    GPIOA->CRH&=0XFFFF0FF0;  //PA8,11推挽输出
    GPIOA->CRH|=0X00003003;
    GPIOA->ODR|=9<<0;        //PA8,11上拉
  
    AFIO->MAPR|=2<<24;      ////关闭JATG,千万不能将SWD也关闭，否则芯片作废，亲测!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    
    led_a_off
    led_b_off
    led_c_off
    led_d_off
}

/* led reflash */
void led_reflash(uint8_t led_value)
{
    if(0x01 & led_value){
        led_a_on
    }else{
        led_a_off
    }
    
    if(0x02 & led_value){
        led_b_on
    }else{
        led_b_off
    }
    
    if(0x04 & led_value){
        led_c_on
    }else{
        led_c_off
    }
    
    if(0x08 & led_value){
        led_d_on
    }else{
        led_d_off
    }
}




