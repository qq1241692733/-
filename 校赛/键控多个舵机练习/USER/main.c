#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "pwm.h"
#include "key.h"

int main(void)
{ 
  u8 key;           //�����ֵ
	u16 led0pwmval=0;  
	u16 led0pwmva2=0;  	//wpm10
	delay_init(168);  //��ʼ����ʱ����
	LED_Init();				//��ʼ��LED�˿� 
	uart_init(115200);//��ʼ�����ڲ�����Ϊ115200
	KEY_Init();       //��ʼ���밴�����ӵ�Ӳ���ӿ�
	LED0=0;				  	//�ȵ������
	TIM14_PWM_Init(20000,84-1);
	TIM10_PWM_Init(20000,84-1);	
	while(1)
	{
		TIM_SetCompare1(TIM14,led0pwmval);//ͨ��1  pwm 14
		TIM_SetCompare1(TIM10, led0pwmva2);   //pwm 9
		key=KEY_Scan(0);		//�õ���ֵ
	   	if(key)
		{					
			switch(key)
			{				 
				case WKUP_PRES:	//
					led0pwmval=20000-1500;
					led0pwmva2=20000-3250;				
					break;
				case KEY0_PRES:	//
					led0pwmval=20000-700;
					led0pwmva2=20000-1400;				
					LED0=!LED0;
					break;
				case KEY1_PRES:	// 
					LED1=!LED1;
				led0pwmval=20000-1500;
				led0pwmva2=20000-3250;
					break;
				case KEY2_PRES:	//��ת180��
				led0pwmval=20000-2500;
				led0pwmva2=20000-5000;				
					break;
			}		
		}
			else delay_ms(20); 
	}

}
