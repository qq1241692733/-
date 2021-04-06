#include "sys.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"
#include "lcd.h"
#include "key.h"  
#include "display.h"
#include "stepmotor.h"	

#include "picture.h"
#include "video.h"
#include "usmart.h"  
#include "malloc.h" 
#include "w25qxx.h"    
#include "sdio_sdcard.h"
#include "ff.h"  
#include "exfuns.h"    
#include "fontupd.h"
#include "text.h"	 
#include "wm8978.h"	 
#include "videoplayer.h" 
#include "timer.h" 

void Turn_around(int angle,int period)  //  ��ת
{
		int x;
		GPIO_ResetBits(GPIOD,GPIO_Pin_13);    // EN ʹ�� 
		GPIO_SetBits(GPIOD,GPIO_Pin_12);    //  ��ת
		for(x = 0; x < angle; x++)            //  
		{
				GPIO_SetBits(GPIOD,GPIO_Pin_11);   //   CLK����
				delay_us(period);
				GPIO_ResetBits(GPIOD,GPIO_Pin_11); //   CLK����
				delay_us(period);    
		}
		GPIO_SetBits(GPIOD,GPIO_Pin_13);    // ͣ
}

int main(void)
{ 
  u8 key;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	KEY_Init();   
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200

	LED_Init();					//��ʼ��LED  
 	LCD_Init();					//LCD ��ʼ�� 	
	LCD_Display_Dir(1);  //����

	W25QXX_Init();				//��ʼ��W25Q128
	usmart_dev.init(168);		//��ʼ��USMART
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ�� 
	my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ�� 
	exfuns_init();				//Ϊfatfs��ر��������ڴ�  
  	f_mount(fs[0],"0:",1); 		//����SD�� 
 	f_mount(fs[1],"1:",1); 		//����FLASH	
	while(font_init()) 			//����ֿ�
	{	    
		LCD_ShowString(30,50,200,16,16,"Font Error!");
		delay_ms(200);				  
		LCD_Fill(30,50,240,66,WHITE);//�����ʾ	     
		delay_ms(200);	
		LED0=!LED0;
	}  	 
	POINT_COLOR=RED;      
	Show_Str(360,30,200,24,"��������",24,0);	
//	delay_ms(1500);

	while(1)
	{
//		key=KEY_Scan(0);		//�õ���ֵ
//	   	if(key)
//		{						   
//			switch(key)
//			{				 
//				case WKUP_PRES:	//���Ʒ�����
//					video_Display();
//					break;
//				case KEY0_PRES:	//����LED0��ת
//					Display();
//					break;
//			}
//		}else delay_ms(10); 
Turn_around(800,600);
	}
	
}


