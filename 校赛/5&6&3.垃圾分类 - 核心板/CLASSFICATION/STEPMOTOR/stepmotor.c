#include "stepmotor.h"	
#include "delay.h"
#include "lcd.h"

void gpio_init()
{
	GPIO_InitTypeDef GPIO_Initstructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;   //ͨ��
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_Init(GPIOF, &GPIO_Initstructure);
	
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;  // PF10 CWת��12 ��   PF2 CLK���� 11 ��    PF4 ENʹ�� 13
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Initstructure.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOD, &GPIO_Initstructure);
	

	

}

void Turn_around1(int angle,int period)  //  ��ת
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

void Turn_around2(int angle,int period)  //  ��ת
{
		int x;
		GPIO_ResetBits(GPIOD,GPIO_Pin_13);    // EN ʹ�� 
		GPIO_ResetBits(GPIOD,GPIO_Pin_12);    //  ��ת
		for(x = 0; x < angle; x++)            //  200������λΪ6Ms������  һ������1.8��  1.8��*200=360��һȦ1.2s  ��ϸ��
		{
				GPIO_SetBits(GPIOD,GPIO_Pin_11);   //   CLK����
				delay_us(period);
				GPIO_ResetBits(GPIOD,GPIO_Pin_11); //   CLK����
				delay_us(period);    
		}
		GPIO_SetBits(GPIOD,GPIO_Pin_13);    // ͣ
}



int garbage_ret()
{
	if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1)==1)  //�ɻ������
	{
		return 1;			
	}
	if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2)==1)  //�к�����
	{
		return 2;
	}
	if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_3)==1)  //��������
	{
		return 3;	
	}
	if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_4)==1)  //��������
	{
		return 4;
	}
	else
		return 0;
}
