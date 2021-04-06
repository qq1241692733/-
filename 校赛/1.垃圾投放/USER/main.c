#include "sys.h"
#include "delay.h"
#include "led.h"
#include "usart.h"

void Turn_around1(int angle,int period);
void Turn_around2(int angle,int period);
int garbage_ret();

int main(void)
{

	u16 a=0;

	delay_init(168);
	time_init(20000,84-1);
	gpio_init();
	GPIO_SetBits(GPIOF,GPIO_Pin_4);    // ͣ


	while(1)         // PF10 CWת��    PF9 CLK����    PF4 ENʹ�� 
  	{	
			while(1)
			{
				a=garbage_ret();
				if(a!=0)
					break;
			}

			switch(a)   
			{
				
				case 1: 
						TIM_SetCompare1(TIM14,20000-1700);			
						delay_ms(1500);
						TIM_SetCompare1(TIM14,20000-1295);  //��
						delay_ms(2000);				
						a=0;
						break;
				
				case 2:   //2��Ͱ
				  	Turn_around1(800,600);
						TIM_SetCompare1(TIM14,20000-1700);
						delay_ms(1200);
						Turn_around2(800,600);
						TIM_SetCompare1(TIM14,20000-1295);  //��
						delay_ms(2000);	
						a=0;
					break;
				
				case 3:   //3��Ͱ
				  	Turn_around1(1600,600);
			
						TIM_SetCompare1(TIM14,20000-1700);
						delay_ms(1500);
						Turn_around2(1600,600);				
						TIM_SetCompare1(TIM14,20000-1295);  //��
						delay_ms(2000);
						a=0;				
					break;
				
				case 4:   // 4껺�Ͱ
				  	Turn_around2(800,600);
						TIM_SetCompare1(TIM14,20000-1700);
						delay_ms(1500);
						Turn_around1(800,600);	
						TIM_SetCompare1(TIM14,20000-1295);  //��
						delay_ms(2000);	
						a=0;			
					break;
				
				default:
					break;
		}
	}	
}
void Turn_around1(int angle,int period)  //  ��ת
{
		int x;
		GPIO_ResetBits(GPIOF,GPIO_Pin_4);    // EN ʹ�� 
		GPIO_SetBits(GPIOF,GPIO_Pin_10);    //  ��ת
		for(x = 0; x < angle; x++)            //  
		{
				GPIO_SetBits(GPIOF,GPIO_Pin_2);   //   CLK����
				delay_us(period);
				GPIO_ResetBits(GPIOF,GPIO_Pin_2); //   CLK����
				delay_us(period);    
		}
		GPIO_SetBits(GPIOF,GPIO_Pin_4);    // ͣ
}

void Turn_around2(int angle,int period)  //  ��ת
{
		int x;
		GPIO_ResetBits(GPIOF,GPIO_Pin_4);    // EN ʹ�� 
		GPIO_ResetBits(GPIOF,GPIO_Pin_10);    //  ��ת
		for(x = 0; x < angle; x++)            //  200������λΪ6Ms������  һ������1.8��  1.8��*200=360��һȦ1.2s  ��ϸ��
		{
				GPIO_SetBits(GPIOF,GPIO_Pin_2);   //   CLK����
				delay_us(period);
				GPIO_ResetBits(GPIOF,GPIO_Pin_2); //   CLK����
				delay_us(period);    
		}
		GPIO_SetBits(GPIOF,GPIO_Pin_4);    // ͣ
}

int garbage_ret()
{
	if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_15)==1)
		return 1;			
	if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_12)==1)
		return 2;	
	if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_13)==1)
		return 3;	
	if(GPIO_ReadInputDataBit(GPIOF, GPIO_Pin_14)==1)
		return 4;
	
}
