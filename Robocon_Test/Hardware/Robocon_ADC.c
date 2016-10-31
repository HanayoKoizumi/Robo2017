/*!
 * @file       Robocon_ADC.c
 * @brief      Robocon����С��ADCģ��
 * @author     HRCT
 * @version    v1.0
 * @date       2016-09-29
 */
 
 #include "Robocon_ADC.h"
 
volatile uint32_t Motor_Cur[3];
 
 static void ADC_Channel_Init(void)
 {
		RCC->APB2ENR |= (1<<9);					//ADCʱ��ʹ��
		RCC->APB2ENR |= (1<<3);					//GPIOB��Cʱ��ʹ��
		RCC->APB2ENR |= (1<<4);
	 
		GPIOB->CRL &= 0xFFFFFF00;				//ģ������ģʽ   B0 B1 C4
		GPIOC->CRL &= 0xFFF0FFFF;
	 
		RCC->APB2RSTR |= (1<<9);				//ADC1��λ
		RCC->APB2RSTR &= ~(1<<9);
		RCC->CFGR |= (3<<14);							//8��Ƶ	9MHz
	 
		ADC1->CR1 &= ~(0xF<<16);				//��������ģʽ
		//ADC1->CR1 &= ~(1<<8);
		ADC1->CR1 |= (1<<8);						//ɨ��ģʽ
		ADC1->CR2 |= (1<<1);						//����ת��ģʽ
		ADC1->CR2 |= (7<<17);						//�������ת��
		ADC1->CR2 |= (1<<8);						//ʹ��DMA
	 
		ADC1->SMPR1 |= (5<<18);					//���ò�������
		ADC1->SMPR1 &= ~(1<<19);
		/*
		ADC1->SMPR2 |= (5<<24);
		ADC1->SMPR2 &= ~(1<<25);
		ADC1->SMPR2 |= (5<<27);
		ADC1->SMPR2 &= ~(1<<28);
		ADC1->SMPR1 |= (5<<12);
		ADC1->SMPR1 &= ~(1<<13);					//ֻ���Һ��ϵ�֪����μĴ�������ô���(*^_^*)		
		*/																//���ˣ�����ֻ���ϵ�֪����(��գ� )���ꡭ��
	 
		ADC1->CR2 |= ((1<<23)+1);
		ADC1->CR2 |= (1<<3);							//������λУ׼�Ĵ���
		while(ADC1->CR2&(1<<3));
		ADC1->CR2 |= (1<<2);							//����ADУ׼
		while(ADC1->CR2&(1<<2));
	 
	 
		ADC1->SQR1 &= ~(0xF<<20);
		ADC1->SQR3 |= (1<<4);							//ͨ��16
		/*
		ADC1->SQR1 &= ~(0xF<<20);
		ADC1->SQR1 |= (2<<20);
		ADC1->SQR3 |= (1<<3);							//ͨ��8
		ADC1->SQR3 |= ((1<<3)+1)<<5);			//ͨ��9
		ADC1->SQR3 |= (0xE<<10);					//ͨ��14
		*/

		ADC1->CR2 |= (1<<22);							//�����������  
		ADC1->CR2 |= (1<<0);							//����д1����ʼת��
 }
 
 
 static void DMA_Channel_Init(void)
 {
		RCC->AHBENR |= (1<<0);
	 
		DMA1_Channel1->CPAR = ((u32)0x40012400+0x4c);			//ADC���ݵ�ַ
		DMA1_Channel1->CMAR = (u32)Motor_Cur;
		DMA1_Channel1->CNDTR = 1;
		//DMA1_Channel1->CNDTR = 3;
		DMA1_Channel1->CCR |= (1<<12);			//ͨ�����ȼ�����
		DMA1_Channel1->CCR &= ~(1<<0);			//���赽�洢��
		DMA1_Channel1->CCR |= (1<<5);				//ѭ��ģʽ
		DMA1_Channel1->CCR &= ~(1<<7);			//�洢����ַ�̶�
		//DMA1_Channel1->CCR |= (1<<7);				//�洢����ַ����
		DMA1_Channel1->CCR &= ~(1<<6);			//�����ַ�̶�
		DMA1_Channel1->CCR |= (1<<10);			//�洢�����ݿ�ȣ�����
		DMA1_Channel1->CCR |= (1<<8);				//�������ݿ�ȣ�����
		
		DMA1_Channel1->CCR |= (1<<0);				//ͨ��1ʹ��
 }
 
 void Current_ADGet_Init(void)
 {
		ADC_Channel_Init();
		DMA_Channel_Init();
 }

 
 

