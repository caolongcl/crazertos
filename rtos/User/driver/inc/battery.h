#ifndef __BATTERY_H__
#define __BATTERY_H__

#include "stm32f10x.h"


#define BAT_CHK_PRD    5000	  //ms
#define BAT_ALARM_VAL  3.7	  //on ground
#define BAT_CHG_VAL    1.0	  // charge battery val.  unit :v



//电压信息结构体
typedef struct
{
    int    bat_ad;             //电压AD值
    float  bat_val;            //电压实际值
    float  bat_real;           //电池的实际电压，用万用表测
    float  ad_ref;                 //AD参考源电压，这里是单片机供电电压，一般在3.3V左右，要实测
    float  ad_input;               //AD采样输入电压--->R15和R17相连的焊盘电压
    float  bat_k;                 //计算电压值系数，用于电压校准
    int    bat_admin;          //电压门限
    char   alarm;									//报警位
    char   chg_st;							//充电状态
}BatInfo;

void bat_check_init(void);
uint16_t get_adc(uint8_t ch) ;
uint16_t get_adc_average(uint8_t ch,uint8_t times);
int get_bat_ad(void);
int get_temp(void);
void bat_check(void);

extern BatInfo battery_info;


#endif
