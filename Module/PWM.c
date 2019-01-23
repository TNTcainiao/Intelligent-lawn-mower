#include "sys.h"
#include "PWM.h"


TIM_HandleTypeDef TIME3_PWM_Handler;					//PWM���
TIM_HandleTypeDef TIME2_PWM_Handler;					
TIM_OC_InitTypeDef TIME3_OC_Init;
TIM_OC_InitTypeDef TIME2_OC_Init;

void TIME3_PWM_Init(void){

	TIME3_PWM_Handler.Instance = TIM3;					//��ʱ��3
	TIME3_PWM_Handler.Init.Prescaler = 90 - 1;				//Ԥ��Ƶ��
	TIME3_PWM_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;		//���ϼ���
	TIME3_PWM_Handler.Init.Period = 500 - 1;				//�Զ�װ��ֵ
	HAL_TIM_PWM_Init(&TIME3_PWM_Handler);				//��ʱ��3��ʼ��
	
	TIME3_OC_Init.OCMode = TIM_OCMODE_PWM1;				//PWMģʽ1
	TIME3_OC_Init.Pulse =  250; 						//���ñȽ�ֵ
	TIME3_OC_Init.OCPolarity = TIM_OCPOLARITY_LOW;			//����Ƚϼ���
	HAL_TIM_PWM_ConfigChannel(&TIME3_PWM_Handler,&TIME3_OC_Init,TIM_CHANNEL_4);			//PWM3ͨ��4��ʼ��

	HAL_TIM_PWM_Start(&TIME3_PWM_Handler,TIM_CHANNEL_4);			//����PWM
	HAL_TIM_PWM_Start_IT(&TIME3_PWM_Handler,TIM_CHANNEL_4);			//����PWM�ж�
}

void TIME2_PWM_Init(void)
{
	TIME2_PWM_Handler.Instance = TIM2;					//��ʱ��2
	TIME2_PWM_Handler.Init.Prescaler = 90 - 1;				//Ԥ��Ƶ��
	TIME2_PWM_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;		//���ϼ���
	TIME2_PWM_Handler.Init.Period = 500 - 1;				//�Զ�װ��ֵ
	HAL_TIM_PWM_Init(&TIME2_PWM_Handler);				//��ʱ��2��ʼ��
	
	TIME2_OC_Init.OCMode = TIM_OCMODE_PWM1;				//PWMģʽ1
	TIME2_OC_Init.Pulse =  250; 						//���ñȽ�ֵ
	TIME2_OC_Init.OCPolarity = TIM_OCPOLARITY_LOW;			//����Ƚϼ���
	HAL_TIM_PWM_ConfigChannel(&TIME2_PWM_Handler,&TIME2_OC_Init,TIM_CHANNEL_2);			//PWM2ͨ��2��ʼ��

	HAL_TIM_PWM_Start(&TIME2_PWM_Handler,TIM_CHANNEL_2);			//����PWM
	HAL_TIM_PWM_Start_IT(&TIME2_PWM_Handler,TIM_CHANNEL_2);			//����PWM�ж�


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
		GPIO_Initure.Alternate=GPIO_AF2_TIM3;	//����Ϊ��ʱ��3ͨ��4
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//��ʼ��PB1

	 }
	if(htim->Instance == TIM2){
	
		GPIO_InitTypeDef GPIO_Initure;
	 
		__HAL_RCC_TIM2_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
		
		 
		GPIO_Initure.Pin = GPIO_PIN_4;
		GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;		//�������
		GPIO_Initure.Pull=GPIO_PULLUP;			//����
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//����
		HAL_GPIO_Init(GPIOC,&GPIO_Initure);
		 
		GPIO_Initure.Pin = GPIO_PIN_7;
		HAL_GPIO_Init(GPIOA,&GPIO_Initure); 
		 
		GPIO_Initure.Pin=GPIO_PIN_1;			//PA1
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//�����������
		GPIO_Initure.Pull=GPIO_PULLUP;			//����
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//����
		GPIO_Initure.Alternate=GPIO_AF1_TIM2;	//����Ϊ��ʱ��2ͨ��2
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//��ʼ��PA1
	
	
	
	
	}
	 
 }

 
 //����TIM3ͨ��4��ռ�ձ�
//compare:�Ƚ�ֵ
void TIM_SetTIM3Compare4(u32 compare)
{
	TIM3->CCR4=compare; 
}

void TIM_SetTIM2Compare2(u32 compare)
{
	TIM2->CCR2=compare; 
}


 