#include "include.h"

#define SPEEDMAX 1000

wheel_speed speed_get = {0};
uint8_t motion_mode = 0;

uint8_t movePointCount = 0;//receiveData的计数值

//原lcd屏幕大小为320*480，映射为0.8m*1.2m
//						(32000,48000)mm
//		---------------------
//		|					|
//		|					|
//		|					|
//		|					|
//		|					|
//		|					|
//		|					|
//		---------------------
//		(0,0)
//	系统开机初始化自身坐标为(0,0)
//	receiveData x和y的最大值为4000
//	目标 x = receiveData.x*2;
//	目标 y = 12000 - receiveData.y*3 

//1600 2400
void Motor_Cal()
{
	if(motion_mode==0)
	{
		//	speed_get = basicLine(speed_set*100, direction_set-180, 0,0);
	}
	else if (motion_mode == 1)
	{
		speed_get = point_to_point(150, -(receiveData[movePointCount].x*0.4), (2400-receiveData[movePointCount].y*0.6),
									 motion.pos_x, motion.pos_y, 0, motion.zangle);

//		if(speed_get.status == SUCCESS)
//		{
//			if(movePointCount < DATASIZE - 1)//防止越界
//			{
//				if(receiveData[movePointCount+1].x == 0&&
//					receiveData[movePointCount+1].y == 4000);//下一位为原始数据，说明路径点已经走完
//				else
//				{
//					movePointCount++;
//				}
//			}
//		}
//		 speed_get = point_to_point(150, -250, 250, 
//		 							 motion.pos_x, motion.pos_y, 0, motion.zangle);		
	}
	if(speed_get.v1>SPEEDMAX)
		speed_get.v1=SPEEDMAX;
	if(speed_get.v2>SPEEDMAX)
		speed_get.v2=SPEEDMAX;
	if(speed_get.v3>SPEEDMAX)
		speed_get.v1=SPEEDMAX;
	
	if(speed_get.v1<-SPEEDMAX)
		speed_get.v1=-SPEEDMAX;
	if(speed_get.v2<-SPEEDMAX)
		speed_get.v2=-SPEEDMAX;
	if(speed_get.v3<-SPEEDMAX)
		speed_get.v1=-SPEEDMAX;
}

void Motor_Run()
{
//	if(!speed_get.status)
//	{
		if(speed_get.v1>=0)
		{
			Motor1_Z(speed_get.v1);
			Motor1_F(0);
		}
		else if(speed_get.v1<0)
		{
			Motor1_Z(0);			
			Motor1_F(-speed_get.v1);
		}	

		if(speed_get.v2>=0)
		{
			Motor2_Z(speed_get.v2);
			Motor2_F(0);
		}
		else if(speed_get.v2<0)
		{
			Motor2_Z(0);			
			Motor2_F(-speed_get.v2);
		}			

		if(speed_get.v3>=0)
		{
			Motor3_Z(speed_get.v3);
			Motor3_F(0);
		}
		else if(speed_get.v3<0)
		{
			Motor3_Z(0);
			Motor3_F(-speed_get.v3);
		}					
//	}
//	else
//	{
//		Motor1_Z(0);
//		Motor1_F(0);				
//		Motor2_Z(0);
//		Motor2_F(0);				
//		Motor3_Z(0);
//		Motor3_F(0);	
//	}
}
