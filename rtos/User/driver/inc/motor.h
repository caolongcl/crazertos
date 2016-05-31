#ifndef __MOTOR_H__
#define __MOTOR_H__

#include "stm32f10x.h"

#define MOTOR_PWM_MAX   999
#define TIM2_PERIOD     999

typedef struct 
{
    int16_t motro1_pwm ;
    int16_t motro2_pwm ;
    int16_t motro3_pwm ;
    int16_t motro4_pwm ; 
}MotorPwm;

void motor_init(void);
void motor_pwmflash(MotorPwm *pmotor);

#endif
