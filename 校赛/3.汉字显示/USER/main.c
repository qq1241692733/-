#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "key.h"  
#include "sram.h"   
#include "malloc.h" 
#include "usmart.h"  
#include "sdio_sdcard.h"    
#include "malloc.h" 
#include "w25qxx.h"    
#include "ff.h"  
#include "exfuns.h"    
#include "fontupd.h"
#include "text.h"	
//ALIENTEK ̽����STM32F407������ ʵ��40
//������ʾ ʵ�� -�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com
//������������ӿƼ����޹�˾    
//���ߣ�����ԭ�� @ALIENTEK 

 
int main(void)
{        
	u32 fontcnt;		  
	u8 i,j;
	u8 fontx[2];//gbk��
	u8 key,t;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	LED_Init();					//��ʼ��LED  
 	LCD_Init();					//LCD��ʼ��  
	LCD_Display_Dir(1);
 	KEY_Init();					//������ʼ��  
	W25QXX_Init();				//��ʼ��W25Q128
	usmart_dev.init(168);		//��ʼ��USMART
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ�� 
	my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ�� 
	exfuns_init();				//Ϊfatfs��ر��������ڴ�  
  	f_mount(fs[0],"0:",1); 		//����SD�� 
 	f_mount(fs[1],"1:",1); 		//����FLASH.
	while(font_init()) 			//����ֿ�
	{
UPD:    
	}  
	
	POINT_COLOR=RED;       
	LCD_ShowString(28,70,840,16,24, "--------------------------------------------------------------.");
	LCD_ShowString(28,85,840,16,24, "|            |           |           |           |           |"); 
	           Show_Str(28,100,840,24,"     ��Ŀ     �ɻ�������   �к�����    ��������    ��������",24,1);  
 
	LCD_ShowString(28,130,840,16,24,"|------------|-----------|-----------|-----------|-----------|");
	LCD_ShowString(28,145,840,16,24,"|            |           |           |           |           |"); 
          	Show_Str(28,160,840,24,"     ���� ",24,1 ); 

	LCD_ShowString(28,190,840,16,24,"|------------|-----------|-----------|-----------|-----------|");
	LCD_ShowString(28,205,840,16,24,"|            |           |           |           |           |"); 
	          Show_Str(28,220,840,24,"     ˳�� ",24,1 ); 

	LCD_ShowString(28,250,840,16,24,"|------------|-----------|-----------|-----------|-----------|");
	LCD_ShowString(28,265,840,16,24,"|            |           |           |           |           |"); 
            Show_Str(28,280,840,24,"   ����״̬ ",24,1 ); 

	LCD_ShowString(28,310,840,16,24,"|------------|-----------|-----------|-----------|-----------|"); 

 	POINT_COLOR=BLUE;  
	
	Show_Str(360,30,200,24,"��������",24,0);				    	 

}







