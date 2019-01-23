#include <sys.h>
void TIME3_PWM_Init(void);
void TIME2_PWM_Init(void);
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim);
void TIM_SetTIM2Compare2(u32 compare);
void TIM_SetTIM3Compare4(u32 compare);

