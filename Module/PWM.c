#include "sys.h"
#include "PWM.h"


TIM_HandleTypeDef TIME3_PWM_Handler;					//PWM句柄
TIM_HandleTypeDef TIME2_PWM_Handler;					
TIM_OC_InitTypeDef TIME3_OC_Init;
TIM_OC_InitTypeDef TIME2_OC_Init;

void TIME3_PWM_Init(void){

	TIME3_PWM_Handler.Instance = TIM3;					//定时器3
	TIME3_PWM_Handler.Init.Prescaler = 90 - 1;				//预分频数
	TIME3_PWM_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;		//向上计数
	TIME3_PWM_Handler.Init.Period = 500 - 1;				//自动装载值
	HAL_TIM_PWM_Init(&TIME3_PWM_Handler);				//定时器3初始化
	
	TIME3_OC_Init.OCMode = TIM_OCMODE_PWM1;				//PWM模式1
	TIME3_OC_Init.Pulse =  250; 						//设置比较值
	TIME3_OC_Init.OCPolarity = TIM_OCPOLARITY_LOW;			//输出比较极性
	HAL_TIM_PWM_ConfigChannel(&TIME3_PWM_Handler,&TIME3_OC_Init,TIM_CHANNEL_4);			//PWM3通道4初始化

	HAL_TIM_PWM_Start(&TIME3_PWM_Handler,TIM_CHANNEL_4);			//启动PWM
	HAL_TIM_PWM_Start_IT(&TIME3_PWM_Handler,TIM_CHANNEL_4);			//启动PWM中断
}

void TIME2_PWM_Init(void)
{
	TIME2_PWM_Handler.Instance = TIM2;					//定时器2
	TIME2_PWM_Handler.Init.Prescaler = 90 - 1;				//预分频数
	TIME2_PWM_Handler.Init.CounterMode = TIM_COUNTERMODE_UP;		//向上计数
	TIME2_PWM_Handler.Init.Period = 500 - 1;				//自动装载值
	HAL_TIM_PWM_Init(&TIME2_PWM_Handler);				//定时器2初始化
	
	TIME2_OC_Init.OCMode = TIM_OCMODE_PWM1;				//PWM模式1
	TIME2_OC_Init.Pulse =  250; 						//设置比较值
	TIME2_OC_Init.OCPolarity = TIM_OCPOLARITY_LOW;			//输出比较极性
	HAL_TIM_PWM_ConfigChannel(&TIME2_PWM_Handler,&TIME2_OC_Init,TIM_CHANNEL_2);			//PWM2通道2初始化

	HAL_TIM_PWM_Start(&TIME2_PWM_Handler,TIM_CHANNEL_2);			//启动PWM
	HAL_TIM_PWM_Start_IT(&TIME2_PWM_Handler,TIM_CHANNEL_2);			//启动PWM中断


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
		GPIO_Initure.Alternate=GPIO_AF2_TIM3;	//复用为定时器3通道4
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);	   	//初始化PB1

	 }
	if(htim->Instance == TIM2){
	
		GPIO_InitTypeDef GPIO_Initure;
	 
		__HAL_RCC_TIM2_CLK_ENABLE();
		__HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
		
		 
		GPIO_Initure.Pin = GPIO_PIN_4;
		GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;		//推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//高速
		HAL_GPIO_Init(GPIOC,&GPIO_Initure);
		 
		GPIO_Initure.Pin = GPIO_PIN_7;
		HAL_GPIO_Init(GPIOA,&GPIO_Initure); 
		 
		GPIO_Initure.Pin=GPIO_PIN_1;			//PA1
		GPIO_Initure.Mode=GPIO_MODE_AF_PP;		//复用推挽输出
		GPIO_Initure.Pull=GPIO_PULLUP;			//上拉
		GPIO_Initure.Speed=GPIO_SPEED_FAST;		//高速
		GPIO_Initure.Alternate=GPIO_AF1_TIM2;	//复用为定时器2通道2
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);	   	//初始化PA1
	
	
	
	
	}
	 
 }

 
 //设置TIM3通道4的占空比
//compare:比较值
void TIM_SetTIM3Compare4(u32 compare)
{
	TIM3->CCR4=compare; 
}

void TIM_SetTIM2Compare2(u32 compare)
{
	TIM2->CCR2=compare; 
}


 