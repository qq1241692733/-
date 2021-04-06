#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "key.h"

#define ON  0
#define OFF 1
#define EN PF3
#define CLK PF2

#define PF2(a) if (a) \
     GPIO_SetBits(GPIOF,GPIO_Pin_2);\
     else  \
     GPIO_ResetBits(GPIOF,GPIO_Pin_2)

#define PF3(a) if (a) \
     GPIO_SetBits(GPIOF,GPIO_Pin_3);\
     else  \
     GPIO_ResetBits(GPIOF,GPIO_Pin_3)
		 
		 
int main(void)
{ 
  u8 i=0;
  u8 key;           //�����ֵ
//	u16 led0pwmval=750;  
	delay_init(168);  //��ʼ����ʱ����
	LED_Init();				//��ʼ��LED�˿� 
	uart_init(115200);//��ʼ�����ڲ�����Ϊ115200
	KEY_Init();       //��ʼ���밴�����ӵ�Ӳ���ӿ�
	LED0=0;				  	//�ȵ������
//	TIM14_PWM_Init(1500,84-1); 
	GPIO_SetBits(GPIOF,GPIO_Pin_3);
	while(1)
	{
//		 GPIO_SetBits(GPIOF,GPIO_Pin_2);
//		delay_ms(4);
//		GPIO_ResetBits(GPIOF,GPIO_Pin_2);
//			delay_ms(2);
//		PF3(1);        ///EN PF3  CLK PF2
//		PF2(1);
//		delay_ms(3);
//		PF2(0);
//		delay_ms(3);
		
//		PF3(0);
//		EN(1);
//		CLK(1);
//		delay_ms(3);
//		CLK(0);
//		delay_ms(3);
//		EN(0);

//		TIM_SetCompare1(TIM14,led0pwmval);
	//	delay_ms(1000);
//	 	led0pwmval=250;
//		delay_ms(200);
//		key=KEY_Scan(0);		//�õ���ֵ
//	   	if(key)
//		{					
//			switch(key)
//			{				 
//				case WKUP_PRES:	
//					{
//						EN(1);
						 for(i=0;i<200;++i)
							{
								CLK(1);
								delay_ms(3);
								CLK(0);
								delay_ms(3);
								EN(0);
							 }
							EN(0);	
//						break;
//				 }
//				case KEY0_PRES:	//

//					LED0=!LED0;
//				
//					break;
//				case KEY1_PRES:	// 
//					LED1=!LED1;

// 
//					break;
//				case KEY2_PRES:	//

//					break;
//			}		
//		}
//			else delay_ms(20); 
	}

}
