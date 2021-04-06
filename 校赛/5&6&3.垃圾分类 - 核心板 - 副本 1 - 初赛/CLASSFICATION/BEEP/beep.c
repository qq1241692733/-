#include "beep.h" 
#include "delay.h"

#include "sys.h"
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

//BEEP IO��ʼ��
void BEEP_Init(void)
{   
  GPIO_InitTypeDef  GPIO_InitStructure;
	NVIC_InitTypeDef   NVIC_InitStructure;
	EXTI_InitTypeDef   EXTI_InitStructure;
	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);//ʹ��SYSCFGʱ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOFʱ��
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//ʹ��GPIOFʱ��
	
  //��ʼ����������Ӧ����GPIOF8
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;//����
  GPIO_Init(GPIOF, &GPIO_InitStructure);//��ʼ��GPIO
  GPIO_ResetBits(GPIOF,GPIO_Pin_8);  //��������Ӧ����GPIOF8���ͣ�

	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;   //����
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
  GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIO
	
}

int isfull(void)
{
	if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)==0)       
	{
		delay_ms(100);     
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_0)==0)    
			{
        Show_Str(246,310,840,24,"��",24,1 ); 				
				delay_ms(10); 
				return 1;
			}
	}
	//***************************************************
	if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1)==0)       
	{
		delay_ms(100);     
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_1)==0)    
			{
        Show_Str(390,310,840,24,"��",24,1 ); 		
				delay_ms(10);
				return 1;				
			}
	}
	//***************************************************
	if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)==0)       
	{
		delay_ms(100);     
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_2)==0)    
			{
        Show_Str(534,310,840,24,"��",24,1 ); 				
				delay_ms(10); 
				return 1;
			}
	}
	//***************************************************
	if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)==0)       
	{
		delay_ms(100);     
		if(GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3)==0)    
			{
        Show_Str(678,310,840,24,"��",24,1 ); 					
				delay_ms(10); 
				return 1;
			}
	}	
	return 0;
}
