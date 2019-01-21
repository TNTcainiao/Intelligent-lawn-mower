#include <sys.h>

void uart1_init(void);
void uart3_init(void);
void HAL_UART_MspInit(UART_HandleTypeDef *huart);
void USART3_IRQHandler(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
void Uart_Receive_IT_Init(void);
