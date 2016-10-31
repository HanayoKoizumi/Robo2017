/*!
 * @file       main.c
 * @brief      Robocon����С��������
 * @author     HRCT
 * @version    v1.0
 * @date       2016-09-27
 */
 
 
 //���ں��İ�ʹ���ڲ�ʱ�ӣ������ε�SystemInit
 
 #include  "include.h"
  float speed_set=0;
 float direction_set=0;
 uint32_t a,b,c=0;
 
 void LED_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED������ʱ��*/
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE); 

		/*ѡ��Ҫ���Ƶ�GPIOB����*/															   
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ��GPIOB0*/
		GPIO_Init(GPIOB, &GPIO_InitStructure);	
		


		/* �ر�����led��	*/
		GPIO_SetBits(GPIOB, GPIO_Pin_0);

}
 
 int main()
 {
	 volatile float temp;
	 

	 RCC_Init();
	 
	 Robocon_PhoTriRacing_Board_Init();
	 
	 Robocon_NVIC_Init();
	 
	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5 , ENABLE);	 		
	 LED_GPIO_Config();
	 setOrigin(0,0); 
				 
	 while(1)
	 {

				
//printf("X_Angle��%.2f\r\nY_Angle��%.2f\r\nZ_Angle��%.2f\r\nX��%.2f\r\nY��%.2f\r\nZ_w��%.2f\r\n",motion.xangle,motion.yangle,motion.zangle,motion.pos_x,motion.pos_y,motion.w_z);

	 } 
		
 }
 











