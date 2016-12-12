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

	ReceiveInit();//2401初始化

	Robocon_PhoTriRacing_Board_Init();

	Robocon_NVIC_Init();

	//DAC1_Init();

	setOrigin(0,0); 
//		 
	while(1)
	{
//		receiveData[1].x = 30;
//		receiveData[1].y = 3980;

//		receiveData[2].x = 40;
//		receiveData[2].y = 3960;

//		receiveData[3].x = 50;
//		receiveData[3].y = 3940;	

//		receiveData[1].x = 60;
//		receiveData[1].y = 3980;

//		receiveData[2].x = 60;
//		receiveData[2].y = 3920;

//		receiveData[3].x = 30;
//		receiveData[3].y = 3980;			
	//printf("X_Angle£º%.2f\r\nY_Angle£º%.2f\r\nZ_Angle£º%.2f\r\nX£º%.2f\r\nY£º%.2f\r\nZ_w£º%.2f\r\n",motion.xangle,motion.yangle,motion.zangle,motion.pos_x,motion.pos_y,motion.w_z);

	} 

}
 











