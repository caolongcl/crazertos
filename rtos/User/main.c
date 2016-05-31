#include "stdio.h"

/* user */
#include "board.h"
#include "user_task.h"

/* FreeRTOS  */
#include "FreeRTOS.h"
#include "portmacro.h"
#include "FreeRTOSConfig.h"
#include "task.h"



static void prvSetupHardware(void);      /* 系统初始化 */

int main()
{
    prvSetupHardware();
    
    vStartLEDFlashTasks( ledFLASH_TASK_PRIORITY );
    
    /* Start the scheduler. */
	vTaskStartScheduler();
    /*while(1)
    {
        delay(900000);
        printf("bat_ad:%d \r\n",get_bat_ad());
    }*/
    return 0;
}
/*-----------------------------------------------------------------------*/

static void prvSetupHardware(void)      /* 系统初始化 */
{   
    uint8_t sys_clock = 0;
//    MotorPwm motor_pwm = {400,300,200,100};
    /* 配置时钟 */
    sys_clock = sys_clock_HSE(9);  /*8M * 9 = 72MHZ*/
    
    /* 设置中断向量表基地址 */
    SCB->VTOR = NVIC_VectTab_FLASH | (0x00 & (uint32_t)0x1FFFFF80);
    
    /* 设置中断组 */
    SCB->AIRCR = AIRCR_VECTKEY_MASK | NVIC_PriorityGroup_4;
    
    /* 配置系统tick时钟源 */
    SysTick->CTRL |= SysTick_CLKSource_HCLK;
    
    /* led */
    led_init();
    
    /* 串口 */
    //uart1_init(sys_clock,USART_BUADRATE);  
    
    /* 电机 */
    //motor_init();
    
    /* 电池电压温度检测 */
    //bat_check_init();
    
    //motor_pwmflash(&motor_pwm);
    //power_on();
    /* 开机信息打印 */
    //printf("sysclk:%dMHz\r\n",sys_clock);
    //printf("baudrate:%d \r\n",USART_BUADRATE);
}
/*-----------------------------------------------------------------------*/



