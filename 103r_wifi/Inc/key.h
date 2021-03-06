#ifndef __KEY_H
#define __KEY_H	 
#include "main.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 



#define KEY0  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)//读取按键0
#define KEY1  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)//读取按键1
#define KEY2  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)//读取按键2 
#define KEY3  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)//读取按键3

 

#define KEY0_PRES 0x50	//KEY0按下
#define KEY1_PRES	0x20	//KEY1按下
#define KEY2_PRES	0x40	//KEY2按下
#define KEY3_PRES 0x60	//KEY_UP按下(即WK_UP/KEY_UP)

u8 KEY_Scan(u8);  	//按键扫描函数					    
#endif
