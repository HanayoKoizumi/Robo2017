/*!
 * @file       Robocon_TIM.c
 * @brief      Robocon����С��TIMӦ��ģ��
 * @author     HRCT
 * @version    v1.0
 * @date       2016-09-27
 */
 
 #include "Robocon_TIM.h"
 
 /********************************����Ϊ��������*************************/
 /***********************************************************************/
 u16 Encode[3];				//�洢����������
 
 void Quadrature_decode_TIM1_Init(void)
 {
	 RCC->APB2ENR |= (1<<11);		//PA8,PA9
	 RCC->APB2ENR |= (1<<0);		//??��3��?1|?��?a??
	 RCC->APB2ENR |= (1<<6);
	 
	 //AFIO->MAPR |= (3<<6);			//������?��3��?
	 GPIO_PinRemapConfig(GPIO_FullRemap_TIM1 ,ENABLE);
	 
	 GPIOE->CRH &= ~(1<<12);
	 GPIOE->CRH &= ~(1<<13);
	 GPIOE->CRH &= ~(1<<4);
	 GPIOE->CRH &= ~(1<<5);
	 
	 GPIOE->CRH |= (1<<14);
	 GPIOE->CRH &= ~(1<<15);
	 GPIOE->CRH |= (1<<6);
	 GPIOE->CRH &= ~(1<<7);
	 
	 TIM1->PSC = 0x0;
	 TIM1->ARR = 0xFFFF;
	 TIM1->CR1 &= ~(3<<8);
	 TIM1->CR1 &= ~(3<<5);
	 
	 TIM1->CCMR1 &= ~(1<<1);
	 TIM1->CCMR1 &= ~(1<<9);
	 TIM1->CCMR1 |= (1<<0);
	 TIM1->CCMR1 |= (1<<8);
	 
	 TIM1->CCER &= ~(1<<1);
	 TIM1->CCER &= ~(1<<5);
	 
	 TIM1->CCMR1 |= 8<<4;
	 
	 TIM1->SMCR &= ~(1<<2);
	 TIM1->SMCR |= (1<<0);
	 TIM1->SMCR |= (1<<1);
	 
	 TIM1->CNT = 0;
	 TIM1->CR1 |= (1<<0);
	 
}
 
void Quadrature_decode_TIM8_Init(void)
{
	 RCC->APB2ENR |= (1<<13);			//PC6,PC7
	 RCC->APB2ENR |= (1<<4);
	 
	 GPIOC->CRL &= ~(1<<24);
	 GPIOC->CRL &= ~(1<<25);
	 GPIOC->CRL &= ~(1<<28);
	 GPIOC->CRL &= ~(1<<29);
	 
	 GPIOC->CRL |= (1<<26);
	 GPIOC->CRL &= ~(1<<27);
	 GPIOC->CRL |= (1<<30);
	 GPIOC->CRL &= ~(1<<31);
	 
	 TIM8->PSC = 0x0;
	 TIM8->ARR = 0xFFFF;
	 TIM8->CR1 &= ~(3<<8);
	 TIM8->CR1 &= ~(3<<5);
	 
	 TIM8->CCMR1 &= ~(1<<1);
	 TIM8->CCMR1 &= ~(1<<9);
	 TIM8->CCMR1 |= (1<<0);
	 TIM8->CCMR1 |= (1<<8);
	 
	 TIM8->CCER &= ~(1<<1);
	 TIM8->CCER &= ~(1<<5);
	 
	 TIM8->CCMR1 |= 8<<4;
	 
	 TIM8->SMCR &= ~(1<<2);
	 TIM8->SMCR |= (1<<0);
	 TIM8->SMCR |= (1<<1);
	 
	 TIM8->CNT = 0;
	 TIM8->CR1 |= (1<<0);
 }
	
void Quadrature_decode_TIM4_Init(void)
{
	 RCC->APB1ENR |= (1<<2);			//PB6,PB7
	 RCC->APB2ENR |= (1<<3);
	 
	 GPIOB->CRL &= ~(1<<24);
	 GPIOB->CRL &= ~(1<<25);
	 GPIOB->CRL &= ~(1<<28);
	 GPIOB->CRL &= ~(1<<29);
	 
	 GPIOB->CRL |= (1<<26);
	 GPIOB->CRL &= ~(1<<27);
	 GPIOB->CRL |= (1<<30);
	 GPIOB->CRL &= ~(1<<31);
	 
	 TIM4->PSC = 0x0;
	 TIM4->ARR = 0xFFFF;
	 TIM4->CR1 &= ~(3<<8);
	 TIM4->CR1 &= ~(3<<5);
	 
	 TIM4->CCMR1 &= ~(1<<1);
	 TIM4->CCMR1 &= ~(1<<9);
	 TIM4->CCMR1 |= (1<<0);
	 TIM4->CCMR1 |= (1<<8);
	 
	 TIM4->CCER &= ~(1<<1);
	 TIM4->CCER &= ~(1<<5);
	 
	 TIM4->CCMR1 |= 8<<4;
	 
	 TIM4->SMCR &= ~(1<<2);
	 TIM4->SMCR |= (1<<0);
	 TIM4->SMCR |= (1<<1);
	 
	 TIM4->CNT = 0;
	 TIM4->CR1 |= (1<<0);
}
	


/********************************����ΪPWM���**************************/
/***********************************************************************/
void PWMout_TIM2_TIM3_Init(u16 CCR11, u16 CCR12, u16 CCR21, u16 CCR22, u16 CCR31, u16 CCR32)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* ����TIM2,TIM3CLK Ϊ 72MHZ */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3, ENABLE); 

  /* GPIOA clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE); 

  /*GPIOA Configuration: TIM2 channel 1,2,3,4 and TIM3 channel 1,2 as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_6 | GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		    // �����������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* Time base configuration */		 
  TIM_TimeBaseStructure.TIM_Period = 999;       //����ʱ����0������999����Ϊ1000�Σ�Ϊһ����ʱ����
  TIM_TimeBaseStructure.TIM_Prescaler = 3;	    //����Ԥ��Ƶ������Ƶ��36MHz, ��������1000, �����PWM����36kHz
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//����ʱ�ӷ�Ƶϵ��������Ƶ(�����ò���)				��ע���ô��Ƕ��ⲿʱ�Ӳ�����ʱ�ӷ�Ƶ
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //���ϼ���ģʽ
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

  /* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;	    //����ΪPWMģʽ1
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	
  TIM_OCInitStructure.TIM_Pulse = CCR11;	   //��������ֵ�������������������ֵʱ����ƽ��������
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;  //����ʱ������ֵС��CCR1_ValʱΪ�ߵ�ƽ
  TIM_OC1Init(TIM2, &TIM_OCInitStructure);	 //ʹ��ͨ��1
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR12;	  //����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC2Init(TIM2, &TIM_OCInitStructure);	  //ʹ��ͨ��2
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR21;	//����ͨ��3�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC3Init(TIM2, &TIM_OCInitStructure);	 //ʹ��ͨ��3
  TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR22;	//����ͨ��4�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC4Init(TIM2, &TIM_OCInitStructure);	//ʹ��ͨ��4
  TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM2, ENABLE);			 // ʹ��TIM2���ؼĴ���ARR
  /* TIM2 enable counter */
  TIM_Cmd(TIM2, ENABLE);                   //ʹ�ܶ�ʱ��2
	
	/* PWM1 Mode configuration: Channel1 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR31;	//����ͨ��1�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC1Init(TIM3, &TIM_OCInitStructure);	 //ʹ��ͨ��1
  TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);

  /* PWM1 Mode configuration: Channel2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = CCR32;	//����ͨ��2�ĵ�ƽ����ֵ���������һ��ռ�ձȵ�PWM
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);	//ʹ��ͨ��2
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM3, ENABLE);			 // ʹ��TIM3���ؼĴ���ARR
  /* TIM3 enable counter */
  TIM_Cmd(TIM3, ENABLE);                   //ʹ�ܶ�ʱ��3
}

/********************************����Ϊ��ʱ�ж�*************************/
/***********************************************************************/
void Interrupt_TIM5_Init(void)
{
//	RCC->APB1ENR |= (1<<4);
	
//	TIM6->PSC = 71;					//�ж����ڣ�(71+1)*(999+1)/72M = 0.001s   (1ms�ж�)
//	TIM6->ARR = 999;
//	
//	TIM6->DIER |= (1<<0);
//	TIM6->CR1 |= (1<<2);
//	
//	TIM6->CNT = 0;
//	
//	TIM6->CR1 |= (1<<0);
	
	  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
		
		/* ����TIM6CLK Ϊ 72MHZ */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 , ENABLE);
    //TIM_DeInit(TIM2);
	
	/* �Զ���װ�ؼĴ������ڵ�ֵ(����ֵ) */
    TIM_TimeBaseStructure.TIM_Period=999;
	
    /* �ۼ� TIM_Period��Ƶ�ʺ����һ�����»����ж� */
	  /* ʱ��Ԥ��Ƶ��Ϊ72 */
    TIM_TimeBaseStructure.TIM_Prescaler= 63;
	
		/* ���ⲿʱ�ӽ��в�����ʱ�ӷ�Ƶ,����û���õ� */
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
		
	
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; 
    TIM_TimeBaseInit(TIM5, &TIM_TimeBaseStructure);
	
    TIM_ClearFlag(TIM5, TIM_FLAG_Update);
	
    TIM_ITConfig(TIM5,TIM_IT_Update,ENABLE);
		
    TIM_Cmd(TIM5, ENABLE);																		

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 , ENABLE);	
	
}
	
	
	
	
	

