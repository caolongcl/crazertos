#include "motor.h"
#include "stm32f10x.h"
#include "FreeRTOSConfig.h"

MotorPwm motor_pwm = {0,0,0,0};

static void tim_motor(void);

void motor_pwmflash(MotorPwm *pmotor)
{		
    if(pmotor->motro1_pwm >= MOTOR_PWM_MAX)	pmotor->motro1_pwm = MOTOR_PWM_MAX;
    if(pmotor->motro2_pwm >= MOTOR_PWM_MAX)	pmotor->motro2_pwm = MOTOR_PWM_MAX;
    if(pmotor->motro3_pwm >= MOTOR_PWM_MAX)	pmotor->motro3_pwm = MOTOR_PWM_MAX;
    if(pmotor->motro4_pwm >= MOTOR_PWM_MAX)	pmotor->motro4_pwm = MOTOR_PWM_MAX;
    
    if(pmotor->motro1_pwm <= 0)	pmotor->motro1_pwm = 0;
    if(pmotor->motro2_pwm <= 0)	pmotor->motro2_pwm = 0;
    if(pmotor->motro3_pwm <= 0)	pmotor->motro3_pwm = 0;
    if(pmotor->motro4_pwm <= 0)	pmotor->motro4_pwm = 0;
    
    TIM2->CCR1 = pmotor->motro1_pwm;
    TIM2->CCR2 = pmotor->motro2_pwm;
    TIM2->CCR3 = pmotor->motro3_pwm;
    TIM2->CCR4 = pmotor->motro4_pwm;        //对定时器寄存器赋值
}


void motor_init(void)
{
    /*-----------------------------------------------------------------*/
    RCC->APB2ENR |= ((uint32_t)0x00000004); //打开外设A的时钟    1<<2
    RCC->APB2ENR |= ((uint32_t)0x00000001); //和复用时钟         1<<0
    RCC->APB1ENR |= ((uint32_t)0x00000001); //打开外设TIM2时钟   1<<0
    /*-----------------------------------------------------------------*/
    GPIOA->CRL &= 0xFFFF0000;       
    GPIOA->CRL |= 0x0000AAAA;               // GPIOA 0 1 2 3;AF_PP;2MHZ
    GPIOA->ODR |= 0x0000000F;               // set to 1
    /*-----------------------------------------------------------------*/
    RCC->APB1RSTR |=  ((uint32_t)0x00000001); //TIM2 set
    RCC->APB1RSTR &= ~((uint32_t)0x00000001); //TIM2 reset
    /*-----------------------------------------------------------------*/
    tim_motor();
}

static void tim_motor(void)
{
    uint16_t tmpcr1 = 0;
    uint16_t tmpccer = 0;//, tmpcr2 = 0;
    uint16_t tmpccmr1 = 0,tmpccmr2 = 0;
    uint16_t PrescalerValue = (uint16_t) (configCPU_CLOCK_HZ / 24000000) - 1;     //控制电机PWM频率 
   /*-----------------------------------------------------------------*/
    // 配置计时器
    tmpcr1 = TIM2->CR1; 
    tmpcr1 &= (uint16_t)(~((uint16_t)(((uint16_t)0x0010) | ((uint16_t)0x0060)))); 
    tmpcr1 |= (uint32_t)((uint16_t)0x0000);                 //上升计数模式
    tmpcr1 &= (uint16_t)(~((uint16_t)(0x0300)));         
    tmpcr1 |= (uint32_t)((uint16_t)0x0000);                 //clock div = 0
    TIM2->CR1 = tmpcr1;
    TIM2->ARR = TIM2_PERIOD ;                               //自动装载值 999
    TIM2->PSC = PrescalerValue;                             //pwm时钟分频
    TIM2->EGR = ((uint16_t)0x0001);                         //装载TIM2_PERIOD Prescaler
    /*-----------------------------------------------------------------*/
    // 配置TIM2为PWM输出模式
    TIM2->CCER &= (uint16_t)(~(uint16_t)(0x1111));  //Reset the CCxE Bit
    tmpccer = TIM2->CCER;
    tmpccer  &= (uint16_t)(~((uint16_t)(0x2222)));  // Reset the Output Polarity level 
    tmpccer  |= ((uint16_t)0x0000);               // Set the Output Compare Polarity :TIM_OCPolarity_High
    tmpccer  |= ((uint16_t)0x1111);                 // Set the Output State :TIM_OutputState_Enable
    TIM2->CCER  = tmpccer;                          // Write to TIM2 CCER 
    
    tmpccmr1 = TIM2->CCMR1;
    tmpccmr1 &= (uint16_t)(~((uint16_t)(0x7373)));  // Reset the Output Compare Mode Bits */
    tmpccmr1 |= ((uint16_t)0x6060);                 // Select the Output Compare Mode :TIM_OCMode_PWM1
    tmpccmr1 &= (uint16_t)~((uint16_t)((uint16_t)0x0808) );// Reset the OC1PE OC2PE Bit
    tmpccmr1 |= ((uint16_t)0x0808);                        //Enable the Output Compare Preload feature 
    TIM2->CCMR1 = tmpccmr1;                         // Write to TIM2 CCMR1
    
    tmpccmr2 = TIM2->CCMR2;
    tmpccmr2 &= (uint16_t)(~((uint16_t)(0x7373)));  // Reset the Output Compare Mode Bits */
    tmpccmr2 |= ((uint16_t)0x6060);                 // Select the Output Compare Mode :TIM_OCMode_PWM1
    tmpccmr2 &= (uint16_t)~((uint16_t)((uint16_t)0x0808));// Reset the OC3PE OC4PE Bit 
    tmpccmr2 |= ((uint16_t)0x0808);                       // Enable the Output Compare Preload feature 
    TIM2->CCMR2 = tmpccmr2;                         // Write to TIM2 CCMR2
    
    TIM2->CCR1  = 0;                                // Set the Capture Compare Register value 
    
    //启动计时器
    TIM2->CR1 |= ((uint16_t)0x0001);                
}
