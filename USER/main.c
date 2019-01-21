#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "Uart.h"
#include "PWM.h"
 
 
int main(void)
{
  
    HAL_Init();                     //初始化HAL库    
    Stm32_Clock_Init(360,25,2,8);   //设置时钟,180Mhz
	delay_init(180);
	uart1_init();					//串口1初始化
	uart3_init();				  //串口3初始化
	Uart_Receive_IT_Init();			//使能串口3接受中断
	TIME3_PWM_Init();
	
	while(1){
		

	}

}



