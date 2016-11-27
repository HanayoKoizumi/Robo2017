/*!
 * @file       Robocon_board.c
 * @brief      Robocon测试小车硬件板
 * @author     HRCT
 * @version    v1.0
 * @date       2016-09-27
 */
 
#include "include.h"

void Robocon_PhoTriRacing_Board_Init(void)
{
	//GPIOE 
	Quadrature_decode_TIM1_Init();	
	//GPIOC	C6 C7	//正交解码初始化
	Quadrature_decode_TIM8_Init();
	//GPIOB B6 B7
	Quadrature_decode_TIM4_Init();

	//GPIOA A0 1 2 3 6 7
	PWMout_TIM2_TIM3_Init(0, 0, 0, 0, 0, 0);						//PWM输出初始化
	//GPIOA A9 A10
	USART1_Init(115200);//串口初始化
	//GPIOC C10 C11
	UART4_Init(115200);
	//GPIOB GPIOC B0 B1 C4
	Current_ADGet_Init();						//电流采集初始化
	//GPIOE E0 E1 E2 E3
	KEY_EXTI_Init();							//按键中断初始化

	Interrupt_TIM5_Init();					//定时器中断初始化
}



//中断优先级初始化
void Robocon_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	//定时器中断优先级配置

	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = TIM5_IRQn;	  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =1;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);


	//按键外部中断优先级配置
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;	  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;	  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;	  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;	  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;	
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

}
 
