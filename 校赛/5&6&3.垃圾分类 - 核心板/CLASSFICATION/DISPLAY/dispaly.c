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


void Display(void)
{    
	u8 a1=0;
	u8 a2=0;
	u8 a3=0;
	u8 a4=0;	
  u8 a=0;
	u8 count=0;	

	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200


	BEEP_Init();
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
	LCD_ShowString(28,70,840,16,24, "--------------------------------------------------------------.");
	LCD_ShowString(28,85,840,16,24, "|            |           |           |           |           |"); 
	           Show_Str(28,100,840,24,"     ��Ŀ     �ɻ�������   �к�����    ��������    ��������",24,1);  
 
	LCD_ShowString(28,130,840,16,24,"|------------|-----------|-----------|-----------|-----------|");
	LCD_ShowString(28,145,840,16,24,"|            |           |           |           |           |"); 
          	Show_Str(28,160,840,24,"     ���� ",24,1 ); 

	LCD_ShowString(28,190,840,16,24,"|------------|-----------|-----------|-----------|-----------|");
	LCD_ShowString(28,205,840,16,24,"|            |           |           |           |           |"); 
//	LCD_ShowString(28,220,840,16,24,"                  --          --          --          --      ");	
	          Show_Str(28,220,840,24,"     ˳�� ",24,1 ); 

	LCD_ShowString(28,250,840,16,24,"|------------|-----------|-----------|-----------|-----------|");
	LCD_ShowString(28,265,840,16,24,"|            |           |           |           |           |"); 
//	LCD_ShowString(28,280,840,16,24,"                  --          --          --          --      ");			
            Show_Str(28,280,840,24,"   ����״̬       --          --          --          --      ",24,1 ); 

	LCD_ShowString(28,310,840,16,24,"|------------|-----------|-----------|-----------|-----------|"); 


 	POINT_COLOR=BLUE;  
	Show_Str(360,30,200,24,"��������",24,0);	
	LCD_ShowxNum(170,160,a1,8,24,0);    //��ʾ
	LCD_ShowxNum(314,160,a2,8,24,0);    //��ʾ
  LCD_ShowxNum(458,160,a3,8,24,0);    //��ʾ	
	LCD_ShowxNum(602,160,a4,8,24,0);    //��ʾ		
	

	
						
	time_init(20000,84-1);

	while(1)         // PF10 CWת��    PF9 CLK����    PF4 ENʹ�� 
  	{	
		
			while(1)
			{
//				if(EXTI_GetITStatus(EXTI_Line1|EXTI_Line2|EXTI_Line3|EXTI_Line0))
//				{

//				}

				a=garbage_ret();
				if(a!=0)					
					break;
			}

			GPIO_SetBits(GPIOF,GPIO_Pin_4);    // ͣ	
			switch(a)   
			{
				
				case 1:   //1��Ͱ    �ɻ�������  PF1
						a1++;		
					  LCD_ShowxNum(170,160,a1,8,24,0);    //��ʾ
				
						count++;				
						LCD_ShowxNum((a-1)*144+120+(a1-1)*35,220,count,8,24,1);    //��ʾ	
						TIM_SetCompare1(TIM13,20000-1550);  //��				
						TIM_SetCompare1(TIM11,20000-1450);		
						delay_ms(1200);
						TIM_SetCompare1(TIM13,20000-1950);
						TIM_SetCompare1(TIM11,20000-700);  //��
						delay_ms(2000);	
						
						a=0;				
						break;
				
				case 2:   //2��Ͱ    �к�����   PF13
						a2++;					
						LCD_ShowxNum(314,160,a2,8,24,0);    //��ʾ	
				
						count++;					
						LCD_ShowxNum((a-1)*144+120+(a2-1)*35,220,count,8,24,1);    //��ʾ		
	
				  	Turn_around1(800,600);
						TIM_SetCompare1(TIM13,20000-1550);  //��				
						TIM_SetCompare1(TIM11,20000-1450);	
						delay_ms(1200);
						Turn_around2(800,600);
						TIM_SetCompare1(TIM13,20000-1950);
						TIM_SetCompare1(TIM11,20000-700);  //��
						delay_ms(2000);	
				

						a=0;				
					break;
				 
				case 3:   //3��Ͱ     ��������   PF14
						a3++;
						LCD_ShowxNum(458,160,a3,8,24,0);    //��ʾ	
				
						count++;						
						LCD_ShowxNum((a-1)*144+120+(a3-1)*35,220,count,8,24,1);    //��ʾ		

				
				  	Turn_around1(1600,600);
						TIM_SetCompare1(TIM13,20000-1550);  //��				
						TIM_SetCompare1(TIM11,20000-1450);	
						delay_ms(1500);
						Turn_around2(1600,600);				
						TIM_SetCompare1(TIM13,20000-1950);
						TIM_SetCompare1(TIM11,20000-700);  //��
						delay_ms(2000);
						a=0;
					break;
				
				case 4:   // 4��Ͱ     ��������   PF15
						a4++;		
						LCD_ShowxNum(602,160,a4,8,24,0);    //��ʾ	
				
						count++;				
						LCD_ShowxNum((a-1)*144+120+(a4-1)*35,220,count,8,24,1);    //��ʾ		

				
				  	Turn_around2(800,600);
						TIM_SetCompare1(TIM13,20000-1550);  //��				
						TIM_SetCompare1(TIM11,20000-1450);	
						delay_ms(1500);
						Turn_around1(800,600);	
						TIM_SetCompare1(TIM13,20000-1950);
						TIM_SetCompare1(TIM11,20000-700);  //��
						delay_ms(2000);	
						a=0;		
					break;
				
				default:
					break;
		}
	}	
}
