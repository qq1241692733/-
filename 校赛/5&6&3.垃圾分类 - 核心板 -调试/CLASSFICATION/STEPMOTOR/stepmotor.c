#include "stepmotor.h"	
#include "delay.h"
#include "lcd.h"

void gpio_init()
{
	GPIO_InitTypeDef GPIO_Initstructure;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;   //通信
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_IN;
	GPIO_Initstructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_Init(GPIOF, &GPIO_Initstructure);
	
	GPIO_Initstructure.GPIO_Pin=GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13;  // PF10 CW转向12 黑   PF2 CLK脉冲 11 白    PF4 EN使能 13
	GPIO_Initstructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_Initstructure.GPIO_OType=GPIO_OType_PP;
	GPIO_Initstructure.GPIO_Speed=GPIO_High_Speed;
	GPIO_Init(GPIOD, &GPIO_Initstructure);
	

	

}

void Turn_around1(int angle,int period)  //  正转
{
		int x;
		GPIO_ResetBits(GPIOD,GPIO_Pin_13);    // EN 使能 
		GPIO_SetBits(GPIOD,GPIO_Pin_12);    //  正转
		for(x = 0; x < angle; x++)            //  
		{
				GPIO_SetBits(GPIOD,GPIO_Pin_11);   //   CLK拉高
				delay_us(period);
				GPIO_ResetBits(GPIOD,GPIO_Pin_11); //   CLK拉低
				delay_us(period);    
		}
		GPIO_SetBits(GPIOD,GPIO_Pin_13);    // 停
}

void Turn_around2(int angle,int period)  //  反转
{
		int x;
		GPIO_ResetBits(GPIOD,GPIO_Pin_13);    // EN 使能 
		GPIO_ResetBits(GPIOD,GPIO_Pin_12);    //  反转
		for(x = 0; x < angle; x++)            //  200个周期位为6Ms的脉冲  一个脉冲1.8°  1.8°*200=360°一圈1.2s  不细分
		{
				GPIO_SetBits(GPIOD,GPIO_Pin_11);   //   CLK拉高
				delay_us(period);
				GPIO_ResetBits(GPIOD,GPIO_Pin_11); //   CLK拉低
				delay_us(period);    
		}
		GPIO_SetBits(GPIOD,GPIO_Pin_13);    // 停
}


static u8 b1=0;
//u8 b2=0;
//u8 b3=0;
//u8 b4=0;	    f 1234
int garbage_ret()
{
	if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_1)==1)  //可回收垃�
	{
		b1=1;
		return 1;			
	}
	if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_2)==1)  //有害垃圾
	{
//		extern u8 b2=1;
		return 2;
	}
	if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_3)==1)  //厨余垃圾
	{
//		b3++;
		return 3;	
	}
	
	if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_4)==1)  //其他垃圾
	{
//		b4++;
		return 4;
	}
	else
		return 0;
}
