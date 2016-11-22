#include "include.h"

wheel_speed speed_get = {0};
uint8_t motion_mode = 0;
uint8_t point_count = 0;//receiveData的计数值

//原lcd屏幕大小为320*480，映射为4m*6m
//						(40000,60000)mm
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
//	目标 x = receiveData.x*10;
//	目标 y = 60000 - receiveData.y*15 
void Motor_Cal()
{
	if(motion_mode==0)
	{
		//	speed_get = basicLine(speed_set*100, direction_set-180, 0,0);
	}
	else if (motion_mode == 1)
	{
		if(speed_get.status)//此值为SUCCESS时执行
		{
			if(point_count < DATASIZE - 1)//防止越界
			{
				if(receiveData[point_count+1].x == 0&&
					receiveData[point_count+1].y == 4000);//下一位为原始数据，说明路径点已经走完
				else
				{
					point_count++;
				}
			}
		}
		speed_get = point_to_point(150, (receiveData[point_count].x*10), (60000-receiveData[point_count].y),
									 motion.pos_x, motion.pos_y, 0, motion.zangle);
		
//				speed_get = closeLoopLine(300, 90,
//	                     0, motion.zangle,
//	                      motion.pos_x, motion.pos_y)	;		
	}
	if(speed_get.v1>1000)
		speed_get.v1=1000;
	if(speed_get.v2>1000)
		speed_get.v2=1000;
	if(speed_get.v3>1000)
		speed_get.v1=1000;
}

void Motor_Run()
{
	if(!speed_get.status)
	{
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
	}
	else
	{
		Motor1_Z(0);
		Motor1_F(0);				
		Motor2_Z(0);
		Motor2_F(0);				
		Motor3_Z(0);
		Motor3_F(0);	
	}
}
