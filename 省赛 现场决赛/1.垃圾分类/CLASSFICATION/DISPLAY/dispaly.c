#include "display.h"
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"

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
#include "beep.h"
#include "pwm.h"
#include "stepmotor.h"	

void dis(u8 count, u8 a) {
		LCD_ShowxNum(60,130+ 24*count,count,8,24,0);    //��ʾ
		Show_Str(60,130+ 24*count,840,24,"                           1         OK��",24,0);
		LCD_ShowxNum(60,130+ 24*count, count, 8, 24, 0);    //��ʾ
		if(a == 1) {
			Show_Str(200,130+ 24*count,840,24,"�ɻ�������",24,1);  
		}else if(a == 2) {
			Show_Str(200,130+ 24*count,840,24,"�к���������",24,1);  
		}else if(a== 3) {
			Show_Str(200,130+ 24*count,840,24,"��������",24,1);  
		}else if(a == 4) {
			Show_Str(200,130+ 24*count,840,24,"��������",24,1);  
		}
		
		if(count == 7) {
			Show_Str(200,346,840,24,"Ͷ����ɣ�",24,1);  
		}
}

void Display(void)
{    
	u8 a=0;
	extern u8 count;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200

	gpio_init();	

	LED_Init();					//��ʼ��LED  
 	LCD_Init();					//LCD ��ʼ�� 	
	LCD_Display_Dir(1);

	W25QXX_Init();				//��ʼ��W25Q128
	usmart_dev.init(168);		//��ʼ��USMART
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ�� 
	my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ�� 
	exfuns_init();				//Ϊfatfs��ر��������ڴ�  
  	f_mount(fs[0],"0:",1); 		//����SD�� 
 	f_mount(fs[1],"1:",1); 		//����FLASH
	
	while(font_init()) 			//����ֿ�
	{
UPD:    
	}  
	POINT_COLOR=RED;   
	LCD_ShowString(28,70,840,16,24, "---------------------------------------------------");
	Show_Str(28,100,840,24,"     ���    �������     ����      �ɹ����",24,1);  
	POINT_COLOR=BLUE;
	Show_Str(360,30,200,24,"��������",24,0);	

	time_init(20000,84-1);
	while(1) {
		while(1)   // PF10 CWת��    PF9 CLK����    PF4 ENʹ�� 
		{
			a=garbage_ret();
			if(a==2)					
				break;
		}
		delay_ms(200);
		a = 0;
		while(1) {
			a=garbage_ret();
			if(a!=0)					
				break;
		}
		
		GPIO_ResetBits(GPIOD,GPIO_Pin_13);    // EN ʹ�� 
		delay_ms(20);
		switch(a)   
		{
			GPIO_ResetBits(GPIOD,GPIO_Pin_13);    // EN ʹ�� 
					TIM_SetCompare1(TIM10,20000-3110);  //��	
					TIM_SetCompare1(TIM13,20000-1090);  //��
			
			case 1:   //1��Ͱ    �ɻ�������  PF1			 
					count++;
					dis( count, a);
			
					TIM_SetCompare1(TIM10,20000-2160);  //��	 ��13
					TIM_SetCompare1(TIM13,20000-1660);  //��
					delay_ms(1200);		
					TIM_SetCompare1(TIM10,20000-3090);  //��	
					TIM_SetCompare1(TIM13,20000-1140);  //��
			
					a=0;	
					break;
			
			case 2:   //2��Ͱ    �к�����   PF13		
					count++;		
					dis( count, a);
						
					Turn_around1(800,600);
					TIM_SetCompare1(TIM10,20000-2160);  //��	 ��13
					TIM_SetCompare1(TIM13,20000-1660);  //��
					delay_ms(1200);		
					TIM_SetCompare1(TIM10,20000-3090);  //��	
					TIM_SetCompare1(TIM13,20000-1140);  //��
					Turn_around2(800,600);

					a=0;				
				break;
			 
			case 3:   //3��Ͱ     ��������   PF14
					count++;
					dis( count, a);
									
					Turn_around1(1600,600);
					TIM_SetCompare1(TIM10,20000-2160);  //��	 ��13
					TIM_SetCompare1(TIM13,20000-1660);  //��
					delay_ms(1200);		
		
					TIM_SetCompare1(TIM10,20000-3090);  //��	
					TIM_SetCompare1(TIM13,20000-1140);  //��
					Turn_around2(1600,600);				
		
					a=0;
				break;
			
			case 4:   // 4��Ͱ     ��������   PF15
					count++;	
					dis( count, a);
					
					Turn_around2(800,600);
					TIM_SetCompare1(TIM10,20000-2160);  //��	 ��13
					TIM_SetCompare1(TIM13,20000-1660);  //��
					delay_ms(1200);
					
					TIM_SetCompare1(TIM10,20000-3090);  //��	
					TIM_SetCompare1(TIM13,20000-1140);  //��
					Turn_around1(800,600);	
					a=0;		
				break;
			
			default:
				break;
			}
		GPIO_ResetBits(GPIOD,GPIO_Pin_13);    // EN ʹ�� 
	}
	
}
