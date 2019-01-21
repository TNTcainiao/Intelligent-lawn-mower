#include "sys.h"
#include "Uart.h"

UART_HandleTypeDef usart1_handler;
UART_HandleTypeDef usart3_handler;

u8 rdata[1];
u8 rec;

void uart1_init()													//设置串口1句柄
{			
	usart1_handler.Instance = USART1;								//设置串口1
	usart1_handler.Init.BaudRate = 115200;							//串口波特率为115200
	usart1_handler.Init.WordLength = UART_WORDLENGTH_8B;			//数据位为8位
	usart1_handler.Init.StopBits = UART_STOPBITS_1;					//1位停止位
	usart1_handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;			//不启用硬件流控制
	usart1_handler.Init.Mode = UART_MODE_TX_RX;						//输入输出模式
	usart1_handler.Init.Parity = UART_PARITY_NONE;					//无奇偶校验位
	
	HAL_UART_Init(&usart1_handler);									//串口初始化设置
}
		
void uart3_init()													//设置串口3句柄
{
	
	usart3_handler.Instance = USART3;								//设置串口3
	usart3_handler.Init.BaudRate = 9600;							//串口波特率为9600
	usart3_handler.Init.WordLength = UART_WORDLENGTH_8B;			//数据位为8位
	usart3_handler.Init.StopBits = UART_STOPBITS_1;					//1位停止位
	usart3_handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;			//不启用硬件流控制
	usart3_handler.Init.Mode = UART_MODE_TX_RX;						//输入输出模式
	usart3_handler.Init.Parity = UART_PARITY_NONE;					//无奇偶校验位
	HAL_UART_Init(&usart3_handler);									//串口初始化设置
		
}


 void HAL_UART_MspInit(UART_HandleTypeDef *huart){					//串口初始化回调函数
 
	 GPIO_InitTypeDef GPIO_Initure;
	 
	if(huart->Instance == USART1){									//若为串口1初始化
	
		__HAL_RCC_GPIOA_CLK_ENABLE();								//启用GPIOA时钟
		__HAL_RCC_USART1_CLK_ENABLE();								//启用串口1时钟
			
		GPIO_Initure.Pin = GPIO_PIN_9;								//设置管脚PA9		
		GPIO_Initure.Mode = GPIO_MODE_AF_PP;						//设置为推挽输出
		GPIO_Initure.Pull = GPIO_PULLUP;							//设置上拉
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;					//高速
		GPIO_Initure.Alternate = GPIO_AF7_USART1;					//复用为串口1
		
		HAL_GPIO_Init(GPIOA,&GPIO_Initure); 						//GPIOA初始化
		GPIO_Initure.Pin = GPIO_PIN_10;								//管脚PA10
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);							
		

		
	}
	if(huart->Instance == USART3){									//若为串口3初始化
		__HAL_RCC_GPIOB_CLK_ENABLE();								//启用GPIOB时钟
		__HAL_RCC_USART3_CLK_ENABLE();								//启用串口3时钟
		GPIO_Initure.Pin = GPIO_PIN_10;								//设置管脚PB10
		GPIO_Initure.Mode = GPIO_MODE_AF_PP;						//设置为推挽输出
		GPIO_Initure.Pull = GPIO_PULLUP;							//设置上拉
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;					//高速
		GPIO_Initure.Alternate = GPIO_AF7_USART3;					//复用为串口3
		
		HAL_GPIO_Init(GPIOB,&GPIO_Initure); 						//GPIOB初始化
		GPIO_Initure.Pin = GPIO_PIN_11;								//管脚PB11
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);
		
		HAL_NVIC_SetPriority(USART3_IRQn,3,3);						//设置串口3中断优先级
		HAL_NVIC_EnableIRQ(USART3_IRQn);							//使能串口3中断
	
	
	
	
	}

 }
 
 
 void USART3_IRQHandler(void){										//中断服务函数
		
	HAL_UART_IRQHandler(&usart3_handler);							//HAL库的串口中断处理函数
	 
	HAL_UART_Receive_IT(&usart3_handler,rdata,sizeof(rdata));		//使能串口3接受中断
 
 }
 
 
void Uart_Receive_IT_Init(void){
	
HAL_UART_Receive_IT(&usart3_handler,rdata,sizeof(rdata));
	
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){			//串口接收中断回调函数
	
	
	
	if(huart->Instance == USART3){
		rec = rdata[0];
		
		HAL_UART_Transmit(&usart1_handler,&rec,sizeof(rec),1000);	//让串口1发送数据到电脑
		if(rec == '1'){
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_RESET);
		
		}
		if(rec=='0'){
		
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_0,GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB,GPIO_PIN_2,GPIO_PIN_SET);
		}
	     
			
		
	}

}
