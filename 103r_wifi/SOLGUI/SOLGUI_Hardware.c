#include"SOLGUI_Type.h"
#include"SOLGUI_Config.h"
#include"SOLGUI_Hardware.h"
#include "main.h"
//*******************����Ļ����ͷ�ļ���*******************
#include "oled.h"


//##########################����Ҫ�û�ʵ�ֵĲ��֡�############################

void SOLGUI_Hardware_Init(void)
{
//=========���û�Ӳ����ʼ����ֲ����=======
	oled_init();
//========================================
}

void SOLGUI_Hardware_FillScreen(u8 GRAM[SCREEN_X_WIDTH][SCREEN_Y_PAGE])
{
//=========���û�Ӳ����Ļ��亯����ֲ����=======
	oled_refreshram(GRAM);
//========================================
}

void SOLGUI_Hardware_ClearScreen(void)
{
//=========���û�Ӳ������������ֲ����=======
	oled_clear();		
//========================================	
}



