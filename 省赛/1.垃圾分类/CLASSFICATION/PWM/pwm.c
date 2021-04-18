#include "pwm.h"
#include "stm32f4xx.h"


void time_init(u32 arr,u32 psc)
{
	GPIO_InitTypeDef GPIO_Initstructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);  	//TIM14ʱ��ʹ��    
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);  	//TIM14ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);  	//
	
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource8,GPIO_AF_TIM13); //GPIOF9����Ϊ��ʱ��14
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource7,GPIO_AF_TIM11); //GPIOF9����Ϊ��ʱ��14
	GPIO_PinAFConfig(GPIOF,GPIO_PinSource6,GPIO_AF_TIM10); //GPIOF9����Ϊ��ʱ��14

	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_6;           //GPIOF9
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_Initstructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_Initstructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOF,&GPIO_Initstructure);              //��ʼ��PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM13,&TIM_TimeBaseStructure);//��ʼ����ʱ��14
	TIM_TimeBaseInit(TIM11,&TIM_TimeBaseStructure);//��ʼ����ʱ��14
	
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM10,&TIM_TimeBaseStructure);//��ʼ����ʱ��14
	//��ʼ��TIM14 Channel1 PWMģʽ	 
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM13, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
	TIM_OC1Init(TIM11, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1f
	TIM_OC1Init(TIM10, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
	
	TIM_OC1PreloadConfig(TIM13, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
 	TIM_OC1PreloadConfig(TIM11, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
 	TIM_OC1PreloadConfig(TIM10, TIM_OCPreload_Enable);  //ʹ��TIM14��CCR1�ϵ�Ԥװ�ؼĴ���
	
  TIM_ARRPreloadConfig(TIM13,ENABLE);//ARPEʹ�� 
  TIM_ARRPreloadConfig(TIM11,ENABLE);//ARPEʹ�� 	
  TIM_ARRPreloadConfig(TIM10,ENABLE);//ARPEʹ�� 	
	
	TIM_Cmd(TIM13, ENABLE);  //ʹ��TIM14
	//TIM_Cmd(TIM11, ENABLE);  //ʹ��TIM14
	TIM_Cmd(TIM10, ENABLE);  //ʹ��TIM14			
}


