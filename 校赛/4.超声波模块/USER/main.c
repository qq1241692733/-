#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "time.h"
#include "beep.h" 
//ALIENTEK ̽����STM32F407������ ʵ��13
//LCD��ʾʵ��-�⺯���汾
//����֧�֣�www.openedv.com
//�Ա����̣�http://eboard.taobao.com  
//������������ӿƼ����޹�˾  
//���ߣ�����ԭ�� @ALIENTEK

int main(void)
{ 
	int tim = 0;
	int s = 0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);      //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	
	LED_Init();					  //��ʼ��LED
 	LCD_Init();           //��ʼ��LCD FSMC�ӿ�
	POINT_COLOR=RED;      //������ɫ����ɫ	
	TIM3_Int_Init(2000,84-1);
	LCD_ShowString(30,136,210,24,24,"S(mm):");	
  while(1) 
	{	
		PBout(8)=1;
		delay_us(20);
		PBout(8)=0;
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 0);
		TIM_Cmd(TIM3,ENABLE);
		while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9) == 1);
		TIM_Cmd(TIM3,DISABLE);
		tim = TIM_GetCounter(TIM3);
		TIM3->CNT = 0;
		s = tim * 0.34 / 2;
		LCD_ShowxNum(30,160, s,6,24,0);		
	} 
}
