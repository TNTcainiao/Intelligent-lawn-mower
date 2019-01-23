#include "sys.h"
#include "Uart.h"
#include "driving.h"


UART_HandleTypeDef usart1_handler;
UART_HandleTypeDef usart3_handler;

u8 driving_rec[1];		//������־λ   0��ɲ�� 	1��ǰ��		2������		3����ת		4����ת		5,�����ͷ		6���ҵ�ͷ



void uart1_init()													//���ô���1���
{			
	usart1_handler.Instance = USART1;								//���ô���1
	usart1_handler.Init.BaudRate = 115200;							//���ڲ�����Ϊ115200
	usart1_handler.Init.WordLength = UART_WORDLENGTH_8B;			//����λΪ8λ
	usart1_handler.Init.StopBits = UART_STOPBITS_1;					//1λֹͣλ
	usart1_handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;			//������Ӳ��������
	usart1_handler.Init.Mode = UART_MODE_TX_RX;						//�������ģʽ
	usart1_handler.Init.Parity = UART_PARITY_NONE;					//����żУ��λ
	
	HAL_UART_Init(&usart1_handler);									//���ڳ�ʼ������
}
		
void uart3_init()													//���ô���3���
{
	
	usart3_handler.Instance = USART3;								//���ô���3
	usart3_handler.Init.BaudRate = 9600;							//���ڲ�����Ϊ9600
	usart3_handler.Init.WordLength = UART_WORDLENGTH_8B;			//����λΪ8λ
	usart3_handler.Init.StopBits = UART_STOPBITS_1;					//1λֹͣλ
	usart3_handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;			//������Ӳ��������
	usart3_handler.Init.Mode = UART_MODE_TX_RX;						//�������ģʽ
	usart3_handler.Init.Parity = UART_PARITY_NONE;					//����żУ��λ
	HAL_UART_Init(&usart3_handler);									//���ڳ�ʼ������
		
}


 void HAL_UART_MspInit(UART_HandleTypeDef *huart){					//���ڳ�ʼ���ص�����
 
	 GPIO_InitTypeDef GPIO_Initure;
	 
	if(huart->Instance == USART1){									//��Ϊ����1��ʼ��
	
		__HAL_RCC_GPIOA_CLK_ENABLE();								//����GPIOAʱ��
		__HAL_RCC_USART1_CLK_ENABLE();								//���ô���1ʱ��
			
		GPIO_Initure.Pin = GPIO_PIN_9;								//���ùܽ�PA9		
		GPIO_Initure.Mode = GPIO_MODE_AF_PP;						//����Ϊ�������
		GPIO_Initure.Pull = GPIO_PULLUP;							//��������
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;					//����
		GPIO_Initure.Alternate = GPIO_AF7_USART1;					//����Ϊ����1
		
		HAL_GPIO_Init(GPIOA,&GPIO_Initure); 						//GPIOA��ʼ��
		GPIO_Initure.Pin = GPIO_PIN_10;								//�ܽ�PA10
		HAL_GPIO_Init(GPIOA,&GPIO_Initure);							
		

		
	}
	if(huart->Instance == USART3){									//��Ϊ����3��ʼ��
		__HAL_RCC_GPIOB_CLK_ENABLE();								//����GPIOBʱ��
		__HAL_RCC_USART3_CLK_ENABLE();								//���ô���3ʱ��
		GPIO_Initure.Pin = GPIO_PIN_10;								//���ùܽ�PB10
		GPIO_Initure.Mode = GPIO_MODE_AF_PP;						//����Ϊ�������
		GPIO_Initure.Pull = GPIO_PULLUP;							//��������
		GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;					//����
		GPIO_Initure.Alternate = GPIO_AF7_USART3;					//����Ϊ����3
		
		HAL_GPIO_Init(GPIOB,&GPIO_Initure); 						//GPIOB��ʼ��
		GPIO_Initure.Pin = GPIO_PIN_11;								//�ܽ�PB11
		HAL_GPIO_Init(GPIOB,&GPIO_Initure);
		
		HAL_NVIC_SetPriority(USART3_IRQn,3,3);						//���ô���3�ж����ȼ�
		HAL_NVIC_EnableIRQ(USART3_IRQn);							//ʹ�ܴ���3�ж�
	
	
	
	
	}

 }
 
 
 void USART3_IRQHandler(void){										//�жϷ�����
		
	HAL_UART_IRQHandler(&usart3_handler);							//HAL��Ĵ����жϴ�����
	 
	HAL_UART_Receive_IT(&usart3_handler,driving_rec,sizeof(driving_rec[0]));		//ʹ�ܴ���3�����ж�
 
 }
 
 
void Uart_Receive_IT_Init(void){
	
HAL_UART_Receive_IT(&usart3_handler,driving_rec,sizeof(driving_rec[0]));
	
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){			//���ڽ����жϻص�����
	
	
	
	if(huart->Instance == USART3){
		
		
		HAL_UART_Transmit(&usart1_handler,&driving_rec[0],sizeof(driving_rec[0]),1000);	//�ô���1�������ݵ�����
		
		if(driving_rec[0] == '0')						//ɲ��
		{
			driving_brake();
			
		
		}
		if(driving_rec[0] == '1')						//ǰ��
		{
			driving_straight(250);
	
		
		}
		if(driving_rec[0] == '2')						//����
		{
			driving_back(150);
	
		
		}
		
		if(driving_rec[0]=='3')							//��ת
		
		{	
			driving_left(90);
			
		}
		if(driving_rec[0] =='4')						//��ת
		{
			
			driving_right(90);
			
		}
		if(driving_rec[0] == '5')						//���ͷ
		{	
			driving_left(180);
		
		}
		if(driving_rec[0] =='6')						//�ҵ�ͷ
		{	
			driving_right(180);
			
		}
	
		
	}

}
