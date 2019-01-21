#include "sys.h"
#include "PWM.h"


TIM_HandleTypeDef TIME3_PWM_Handler;					//PWM句柄
TIM_OC_InitTypeDef TIME3_OC_Init;

void TIME3_PWM_Init(void){

	TIME3_PWM_Handler.Instance = TIM3;					//定时器3
	TIME3_PWM_Handler.Init.Prescaler = 90 - 1;				//预分频数
	TIME3_PWM_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;		//向上计数
	TIME3_PWM_Handler.Init.Period = 500 - 1;				//自动装载值
	HAL_TIM_PWM_Init(&TIME3_PWM_Handler);				//定时器3初始化
	
	TIME3_OC_Init.OCMode = TIM_OCMODE_PWM1;				//PWM模式1
	TIME3_OC_Init.Pulse =  250; 						//设置比较值
	TIME3_OC_Init.OCPolarity = TIM_OCPOLARITY_LOW;			//输出比较极性
	HAL_TIM_PWM_ConfigChannel(&TIME3_PWM_Handler,&TIME3_OC_Init,TIM_CHANNEL_4);			//PWM通道初始化

	HAL_TIM_PWM_Start(&TIME3_PWM_Handler,TIM_CHANNEL_4);			//启动PWM
	HAL_TIM_PWM_Start_IT(&TIME3_PWM_Handler,TIM_CHANNEL_4);			//启动PWM中断
}



 void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim){				//PWM初始化回调函数
	 if(htim->Instance == TIM3){
	 
		GPIO_InitTypeDef GPIO_Initure;
	 
		__HAL_RCC_TIM3_CLK_ENABLE();
		__HAL_RCC_GPIOB_CLK_ENABLE();
	 
		 
		GPIO_Initure.Pin = GPIO_PIN_0;
		GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;		//推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//高速
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);
		 
		GPIO_Initure.Pin = GPIO_PIN_2;
		HAL_GPIO_Init(GPIOB,&GPIO_Initure); 
		 
		GPIO_Initure.Pin=GPIO_PIN_1;			//PB1
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//高速
		GPIO_Initure.Alternate=GPIO_AF2_TIM3;	//复用为USART1
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//初始化PB1

	 }

 }

 
 