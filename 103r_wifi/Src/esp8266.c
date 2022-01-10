#include "esp8266.h"
#include "usart.h"
#include "delay.h"
#include "string.h"
#include "oled.h"
#include "adc.h"

u16 usart1_rx_sta=0x0000;
extern u8 usart1_rx_buf[max_buf];
char cmd_printf[100]="";
char check_printf[100]="";
extern int switch_reg;
u16 esp8266_reg=0x0000;

u8 esp8266_send_cmd(u8* cmd, u8* ack, u8 waittime)
{
	u8 res=0;
	uart1printf("%s\r\n",cmd);
//	ack_determine(cmd);
//	oled_printf(cmd_printf,1);
	while(waittime--)
	{
		delay_ms(10);
		if((usart1_rx_sta&0x8000)==0x8000)
		{
			if(atk_8266_check_cmd(ack))
			{
				res=0;
//				oled_printf(check_printf,3);
				break;
			}
			res=2;//get the wrong return.
//			oled_printf("get the wrong return",1);
		}
	}
	usart1_rx_sta=0;
//	memset(usart1_rx_buf,0,sizeof(usart1_rx_buf));
	if(waittime==0) res=1;
	return res;
}
	
u8 atk_8266_check_cmd(u8 *str)
{
	char* strx=0;
	usart1_rx_buf[usart1_rx_sta&=0x7fff]=0;
	strx=strstr((const char*)usart1_rx_buf,(const char*)str);
	if(strx!=0) return 1;
	else return 0;
}

void ack_determine(char* strings)
{
	char ate0[]="ATE0";
	char cwmmode[]="AT+CWMODE=1";
	char rst[]="AT+RST";
	char cwjap[]="AT+CWJAP";
	char cipstart[]="AT+CIPSTART";
	char send[]="AT+CIPSEND";
	char tcp[]="AT+CIPSTART";
	char ipmode[]="AT+CIPMODE=1";
	char ipclose[]="AT+CIPCLOSE";
	
	if((strcmp(strings,ate0))==0)
	{
		strcpy(cmd_printf,"turn off the loopback mode.");
		strcpy(check_printf,"turn off loopback successfully.");
	}
	else if((strcmp(strings,cwmmode))==0)
	{
		strcpy(cmd_printf,"set in sta mode.");
		strcpy(check_printf,"set in sta mode successfully.");
	}
	else if((strcmp(strings,rst))==0)
	{
		strcpy(cmd_printf,"module resetting.");
		strcpy(check_printf,"reset successfully.");
	}
	else if((strstr(strings,cwjap))!=0)
	{
		strcpy(cmd_printf,"trying connecting WIFI.");
		strcpy(check_printf,"WIFI connect successfully.");
	}
	else if((strstr(strings,cipstart))!=0)
	{
		strcpy(cmd_printf,"Establishing TCP connection.");
		strcpy(check_printf,"TCP connect successfully.");
	}
	else if((strcmp(strings,send))==0)
	{
		strcpy(cmd_printf,"sending command.");
		strcpy(check_printf,"please send message");
	}
	else if((strstr(strings,tcp))!=0)
	{
		strcpy(cmd_printf,"tcp connecting.");
		strcpy(check_printf,"tcp service has established");
	}
	else if((strcmp(strings,ipmode))==0)
	{
		strcpy(cmd_printf,"transparent mode.");
		strcpy(check_printf,"transparent mode");
	}
	
}

void esp8266_init(void)
{
	esp8266_send_cmd("ATE0","OK",200);
	delay_ms(1000);
	esp8266_send_cmd("AT+CWMODE=1","OK",200);
	delay_ms(1000);
	esp8266_send_cmd("AT+CWAUTOCONN=0","OK",200);
	delay_ms(1000);
	esp8266_send_cmd("AT+RST","Version",200);
	delay_ms(1000);
}

void esp8266_send_data(u8* data)
{
	uart1printf("%s\r\n",data);
}

u8 atk_8266_quit_trans(void)
{
	while((USART1->SR&0X40)==0);	//等待发送空
	USART1->DR='+';      
	delay_ms(15);					//大于串口组帧时间(10ms)
	while((USART1->SR&0X40)==0);	//等待发送空
	USART1->DR='+';      
	delay_ms(15);					//大于串口组帧时间(10ms)
	while((USART1->SR&0X40)==0);	//等待发送空
	USART1->DR='+';      
	delay_ms(15);					//等待500ms
//	esp8266_send_cmd("AT","OK",20);//退出透传判断.
}
/**
  * @brief  through inputkey decide whether init esp8266 wifi modular.
	* @param  switch_reg: switch_reg is a global variable which has 
	*					32bits, each bit can be a switch.
  * @retval nothing
  */
void esp_initjudge(void)
{
	static u8 flag=1;
	if((switch_reg>>0)&0x01) 
	{
		if(flag==1)
		{
			esp8266_init();
			flag=0;
		}
	}
	else 
	{
		if(((switch_reg>>0)&0x01)==0)
		{
			if(flag==0) 
			{
				flag=1;
			}
		}
	}
}
/**
  * @brief  through inputkey decide whether esp8266 wifi modular connect ap.
	* @param  switch_reg: switch_reg is a global variable which has 
	*					32bits, each bit can be a switch.
  * @retval nothing
  */
void esp_connectjudge(void)
{
	static u8 flag=1;
	if((switch_reg>>1)&0x01) 
	{
		if(flag==1)
		{
			esp8266_send_cmd("AT+CIPMUX=0","OK",200);
			delay_ms(200);
			esp8266_send_cmd("AT+CWJAP=\"A204_01\",\"junhua.zhao.01\"","OK",200);
			delay_ms(10);
			flag=0;
		}
	}
	else 
	{
		if(((switch_reg>>1)&0x01)==0)
		{
			if(flag==0) 
			{
				esp8266_send_cmd("AT+CWQAP","OK",200);
				delay_ms(10);
				flag=1;
			}
		}
	}
}

void esp_tcpjudge(void)
{
	static u8 flag=1;
	if((switch_reg>>2)&0x01) 
	{
		if(flag==1)
		{
			esp8266_send_cmd("AT+CIPSTART=\"TCP\",\"192.168.68.170\",8086","OK",200);
			delay_ms(10);
			flag=0;
		}
	}
	else 
	{
			if(((switch_reg>>2)&0x01)==0)
		{
			if(flag==0) 
			{
				esp8266_send_cmd("AT+CIPCLOSE","OK",200);
				delay_ms(10);
				flag=1;
			}
		}
	}
}

void esp_senddatajudge(void)
{
	static u8 flag=1;
	if((switch_reg>>3)&0x01) 
	{
		if(flag==1)
		{
			esp8266_send_cmd("AT+CIPMODE=1","OK",200);
			delay_ms(10);
			esp8266_send_cmd("AT+CIPSEND","OK",200);
			delay_ms(10);
			TIM7->CNT=0;
			TIM7->CR1|=1<<0; 
			flag=0;
		}
	}
	else 
	{
		if(flag==0) 
		{
			TIM7->CR1&=0x00;
			delay_ms(10);
			atk_8266_quit_trans();
			flag=1;
		}
	}
}