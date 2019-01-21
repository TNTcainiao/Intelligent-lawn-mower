#include "sys.h"
#include "Uart.h"

UART_HandleTypeDef usart1_handler;
UART_HandleTypeDef usart3_handler;

u8 rdata[1];
u8 rec;

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
	 
	HAL_UART_Receive_IT(&usart3_handler,rdata,sizeof(rdata));		//ʹ�ܴ���3�����ж�
 
 }
 
 
void Uart_Receive_IT_Init(void){
	
HAL_UART_Receive_IT(&usart3_handler,rdata,sizeof(rdata));
	
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){			//���ڽ����жϻص�����
	
	
	
	if(huart->Instance == USART3){
		rec = rdata[0];
		
		HAL_UART_Transmit(&usart1_handler,&rec,sizeof(rec),1000);	//�ô���1�������ݵ�����
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
