#ifndef __KEY_H
#define __KEY_H	 
#include "main.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 



#define KEY0  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_1)//��ȡ����0
#define KEY1  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_3)//��ȡ����1
#define KEY2  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_4)//��ȡ����2 
#define KEY3  HAL_GPIO_ReadPin(GPIOB,GPIO_PIN_5)//��ȡ����3

 

#define KEY0_PRES 0x50	//KEY0����
#define KEY1_PRES	0x20	//KEY1����
#define KEY2_PRES	0x40	//KEY2����
#define KEY3_PRES 0x60	//KEY_UP����(��WK_UP/KEY_UP)

u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
