/*!
 * @file       Robocon_board.c
 * @brief      Robocon����С��Ӳ����
 * @author     HRCT
 * @version    v1.0
 * @date       2016-09-27
 */
 
#include "include.h"

void Robocon_PhoTriRacing_Board_Init(void)
{
	//GPIOE 
	Quadrature_decode_TIM1_Init();	
	//GPIOC	C6 C7	//���������ʼ��
	Quadrature_decode_TIM8_Init();
	//GPIOB B6 B7
	Quadrature_decode_TIM4_Init();

	//GPIOA A0 1 2 3 6 7
	PWMout_TIM2_TIM3_Init(0, 0, 0, 0, 0, 0);						//PWM�����ʼ��
	//GPIOA A9 A10
	USART1_Init(115200);//���ڳ�ʼ��
	//GPIOC C10 C11
	UART4_Init(115200);
	//GPIOB GPIOC B0 B1 C4
	Current_ADGet_Init();						//�����ɼ���ʼ��
	//GPIOE E0 E1 E2 E3
	KEY_EXTI_Init();							//�����жϳ�ʼ��

	Interrupt_TIM5_Init();					//��ʱ���жϳ�ʼ��
}



//�ж����ȼ���ʼ��
void Robocon_NVIC_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	//��ʱ���ж����ȼ�����

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


	//�����ⲿ�ж����ȼ�����
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
 
