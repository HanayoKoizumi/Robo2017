/*!
 * @file       Robocon_Debug.c
 * @brief      Robocon����С������ģ��
 * @author     HRCT
 * @version    v1.0
 * @date       2016-09-29
 */
 
#include "Robocon_Debug.h"

/**************************����Ϊ��ͨ����*********************************/
/*************************************************************************/
void KEY_EXTI_Init(void)
{
		RCC->APB2ENR |= (1<<6);		//�˿�Eʱ�ӿ���
		RCC->APB2ENR |= (1<<0);		//��������AFIOʱ�ӿ���
	
		GPIOE->CRL &= 0xFFFF0000;		//PE0��1��2��3	//����ģʽ
	
		GPIOE->CRL |= (1<<3);
		GPIOE->CRL |= (1<<7);
		GPIOE->CRL |= (1<<11);
		GPIOE->CRL |= (1<<15);		//��/����ģʽ			ע�⸴λֵ����������������������������������������
		
		GPIOE->ODR |= (1<<0);
		GPIOE->ODR |= (1<<1);
		GPIOE->ODR |= (1<<2);
		GPIOE->ODR |= (1<<3);		//����
		
		AFIO->EXTICR[0] |= (1<<2);		//EXTI��0��1��2��3��PE�ܽ�0��1��2��3����
		AFIO->EXTICR[0] |= (1<<6);
		AFIO->EXTICR[0] |= (1<<10);
		AFIO->EXTICR[0] |= (1<<14);
	
		EXTI->IMR |= (1<<0);			//EXTI��0
		EXTI->FTSR |= (1<<0);			//EXTI��0�½��ش���
		EXTI->IMR |= (1<<1);			//EXTI��1
		EXTI->FTSR |= (1<<1);			//EXTI��1�½��ش���
		EXTI->IMR |= (1<<2);			//EXTI��2
		EXTI->FTSR |= (1<<2);			//EXTI��2�½��ش���
		EXTI->IMR |= (1<<3);			//EXTI��3
		EXTI->FTSR |= (1<<3);			//EXTI��3�½��ش���
		
}
