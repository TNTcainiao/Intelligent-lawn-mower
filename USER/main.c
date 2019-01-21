#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "Uart.h"
#include "PWM.h"
 
 
int main(void)
{
  
    HAL_Init();                     //��ʼ��HAL��    
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
	delay_init(180);
	uart1_init();					//����1��ʼ��
	uart3_init();				  //����3��ʼ��
	Uart_Receive_IT_Init();			//ʹ�ܴ���3�����ж�
	TIME3_PWM_Init();
	
	while(1){
		

	}

}



