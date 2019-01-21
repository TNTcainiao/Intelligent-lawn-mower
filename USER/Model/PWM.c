#include "sys.h"
#include "PWM.h"


TIM_HandleTypeDef TIME3_PWM_Handler;					//PWM���
TIM_OC_InitTypeDef TIME3_OC_Init;

void TIME3_PWM_Init(void){

	TIME3_PWM_Handler.Instance = TIM3;					//��ʱ��3
	TIME3_PWM_Handler.Init.Prescaler = 90 - 1;				//Ԥ��Ƶ��
	TIME3_PWM_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;		//���ϼ���
	TIME3_PWM_Handler.Init.Period = 500 - 1;				//�Զ�װ��ֵ
	HAL_TIM_PWM_Init(&TIME3_PWM_Handler);				//��ʱ��3��ʼ��
	
	TIME3_OC_Init.OCMode = TIM_OCMODE_PWM1;				//PWMģʽ1
	TIME3_OC_Init.Pulse =  250; 						//���ñȽ�ֵ
	TIME3_OC_Init.OCPolarity = TIM_OCPOLARITY_LOW;			//����Ƚϼ���
	HAL_TIM_PWM_ConfigChannel(&TIME3_PWM_Handler,&TIME3_OC_Init,TIM_CHANNEL_4);			//PWMͨ����ʼ��

	HAL_TIM_PWM_Start(&TIME3_PWM_Handler,TIM_CHANNEL_4);			//����PWM
	HAL_TIM_PWM_Start_IT(&TIME3_PWM_Handler,TIM_CHANNEL_4);			//����PWM�ж�
}



 void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim){				//PWM��ʼ���ص�����
	 if(htim->Instance == TIM3){
	 
		GPIO_InitTypeDef GPIO_Initure;
	 
		__HAL_RCC_TIM3_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
	 
		 
		GPIO_Initure.Pin = GPIO_PIN_0;
		GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;		//�������
		GPIO_Initure.Pull=GPIO_PULLUP;			//����
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//����
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);
		 
		GPIO_Initure.Pin = GPIO_PIN_2;
		HAL_GPIO_Init(GPIOB,&GPIO_Initure); 
		 
		GPIO_Initure.Pin=GPIO_PIN_1;			//PB1
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
		GPIO_Initure.Pull=GPIO_PULLUP;			//����
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//����
		GPIO_Initure.Alternate=GPIO_AF2_TIM3;	//����ΪUSART1
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//��ʼ��PB1

	 }

 }

 
 