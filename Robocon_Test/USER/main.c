/*!
 * @file       main.c
 * @brief      Robocon²âÊÔÐ¡³µÖ÷³ÌÐò
 * @author     HRCT
 * @version    v1.0
 * @date       2016-09-27
 */
 
 
//ÓÉÓÚºËÐÄ°åÊ¹ÓÃÄÚ²¿Ê±ÖÓ£¬¹ÊÆÁ±ÎµôSystemInit

#include  "include.h"
float speed_set=0;
float direction_set=0;
uint32_t a,b,c=0;



int main()
{
	RCC_Init();
	// SPI1 A4 A5 A6 A7
	ReceiveInit();//2401初始化

	Robocon_PhoTriRacing_Board_Init();

	Robocon_NVIC_Init();

	DAC1_Init();

	setOrigin(0,0); 
		 
	while(1)
	{
		ReceiveData();
	//printf("X_Angle£º%.2f\r\nY_Angle£º%.2f\r\nZ_Angle£º%.2f\r\nX£º%.2f\r\nY£º%.2f\r\nZ_w£º%.2f\r\n",motion.xangle,motion.yangle,motion.zangle,motion.pos_x,motion.pos_y,motion.w_z);

	} 

}
 











