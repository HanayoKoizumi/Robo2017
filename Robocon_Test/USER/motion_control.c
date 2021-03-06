/**
******************************************************************************
* @file    Action_motion_control.c
* @author  ACTION
* @version V1.0
* @date    2016.4.5
* @brief   motion control
*/
/* Includes -------------------------------------------------------------------*/
#include "include.h"

/* Private  typedef -----------------------------------------------------------*/
/* Private  define ------------------------------------------------------------*/
#define Kp_ANG       10.0f    //角度闭环的PID参数 
#define Ki_ANG       0.0f
#define Kd_ANG       0.0f

#define Kp_POS       1.0f    //位置闭环的PID参数
#define Ki_POS       0.0f
#define Kd_POS       0.0f

#define Kp_END       1.0f    //终点闭环的PID参数
#define Ki_END		   0.0f
#define Kd_END		   0.0f

#define PID_ANG_OUT_MAX     1000     //角度闭环的输出最大值
#define PID_POS_OUT_MAX       45     //位置闭环的输出最大值

#define END_ERR_ALLOW       100
#define END_VEL_ALLOW       100

#define ACC_MAX   100.0f  //电机减速速能力

#define dt 0.01f            // 控制周期 10ms
/* Private  macro -------------------------------------------------------------*/
#define ANGLE_TO_RAD(x) (x)/180.0f*3.14159f
#define RAD_TO_ANGLE(x) (x)/3.14159f*180.0f
/* Private  variables ---------------------------------------------------------*/
static float origin_cll_x=0;   //位置闭环和点到点的起点
static float origin_cll_y=0;
static float err_pos_sum = 0, err_ang_sum = 0;
static float err_pos_last = 0, err_ang_last = 0;

/* Extern   variables ---------------------------------------------------------*/
/* Extern   function prototypes -----------------------------------------------*/
/* Private  function prototypes -----------------------------------------------*/
/* Private  functions ---------------------------------------------------------*/
/* Exported function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/
/**
* @brief  开环直线加上旋转
* @param  Vel:车的和速度（正数 Vel>0）
* @param  ward:车的行进方向
                -180到+180
* @param  Rotate:车自身的旋转速度（正数时右旋 俯视图）
* @param  selfAngle:车自身的姿态角度
* @retval wheel_speed:底盘应该达到的速度
* @author ACTION
*/
wheel_speed basicLine(float vel, float ward, float Rotate,float selfAngle)
{
  wheel_speed speed_out;
  /* 计算当底盘旋转后底盘应该的前进方向 */
  ward = ward - selfAngle; 

  /* 坐标系转换 */
  ward= ward;

  /* 分解计算出三个轮的速度 */
  speed_out.v1 = vel*(float)cos(ANGLE_TO_RAD(ward)) + Rotate;
  speed_out.v2 = vel*(float)cos(ANGLE_TO_RAD(ward+120)) + Rotate;
  speed_out.v3 = vel*(float)cos(ANGLE_TO_RAD(120-ward)) + Rotate;

  speed_out.status = FAILURE;
  return speed_out;
}

/**
* @brief  直线闭环的原点设置
* @param  pos_x:底盘坐标
* @param  pos_y:底盘坐标
* @retval none
* @author ACTION
*/
void setOrigin(float pos_x, float pos_y)
{
	origin_cll_x = pos_x;
	origin_cll_y = pos_y;

	err_ang_sum = 0;
	err_pos_sum = 0;

	err_pos_last = 0;
	err_ang_last = 0;
}
/**
* @brief  点到直线距离计算
* @param  ward:直线方向
* @param  line_posx：直线上点x坐标
* @param  line_posy：直线上点y坐标
* @param  posx：参考值
* @param  posy：实际值
* @retval err_pos： 距离
* @author ACTION
*/
float distanceCal(float ward,
	              float line_posx, float line_posy,
	              float posx,      float posy)
{
	float err_pos;
	float dir_x, dir_y;//方向向量
	float act_x, act_y;
	/* 计算位置误差 */
	ward = ward + 90;
	if (ward > 180)
		ward = ward - 360;
	if (ward < -180)
		ward = ward + 360;
	ward = (float)ANGLE_TO_RAD(ward);

	/* 点到直线距离计算，方向向量法 */
	dir_x = (float)cos(ward);
	dir_y = (float)sin(ward);
	act_x = line_posx - posx;
	act_y = line_posy - posy;

	err_pos = dir_x*act_x + dir_y*act_y;

	return err_pos;
}
/**
* @brief  直线闭环
* @param  vel:车的速度（正数 Vel>0）
* @param  ward：前进方向
          -180到+180
* @param  ex_Ang：参考值
* @param  act_Ang：实际值
* @param  pos_x:底盘坐标
* @param  pos_y:底盘坐标
* @retval wheel_speed:底盘应该达到的速度
* @author ACTION
*/
wheel_speed closeLoopLine(float vel,    float ward,
	                      float ex_Ang, float act_Ang,
	                      float pos_x,  float pos_y)
{
	float err_pos, err_pos_v;
	float err_ang, err_ang_v;

	float PID_ang_out;
	float PID_pos_out;

	wheel_speed speed_out;

	err_pos = distanceCal(ward,origin_cll_x,origin_cll_y,pos_x,pos_y);

	/* 计算位置PID三个环节 */
	err_pos_sum = err_pos_sum + err_pos;
	err_pos_v = err_pos - err_pos_last;
	err_pos_last = err_pos;
	PID_pos_out = Kp_POS*err_pos + Ki_POS*err_pos_sum + Kd_POS*err_pos_v;
	/* 最大输出限制 */
	if (PID_pos_out > PID_POS_OUT_MAX)
	{
		PID_pos_out = PID_POS_OUT_MAX;
	}
	else if (PID_pos_out < -PID_POS_OUT_MAX)
	{
		PID_pos_out = -PID_POS_OUT_MAX;
	}

	/* 计算角度PID三个环节 */
	err_ang = -ex_Ang + act_Ang;
	err_ang_sum = err_ang_sum + err_ang;
	err_ang_v = err_ang - err_ang_last;
	err_ang_last = err_ang;
	PID_ang_out = Kp_ANG*err_ang + Ki_ANG*err_ang_sum + Kd_ANG*err_ang_v;
	if (PID_ang_out > PID_ANG_OUT_MAX)
	{
		PID_ang_out = PID_ANG_OUT_MAX;
	}
	else if (PID_ang_out < -PID_ANG_OUT_MAX)
	{
		PID_ang_out = -PID_ANG_OUT_MAX;
	}
	
	speed_out=basicLine(vel / (float)cos(ANGLE_TO_RAD(PID_pos_out)), ward + PID_pos_out, PID_ang_out, act_Ang);
	speed_out.status = FAILURE;
	return speed_out;
}

/**
* @brief  从一点到另一点直线
* @param  vel:车的速度（正数 Vel>0）
* @param  end_posx：目标点x坐标
* @param  end_posy：目标点y坐标
* @param  ex_Ang：参考值
* @param  act_Ang：实际值
* @retval wheel_speed:底盘的速度分配
          SUCCESS:成功到达终点
          FAILURE:还未到达终点
* @author ACTION
*/
wheel_speed point_to_point(float vel,
	float end_posx, float end_posy,
	float pos_x, float pos_y,
	float ex_Ang, float act_Ang)
{
	wheel_speed speed_out;
	float reduce_distance=0;
	static float distance;  //减速距离，当前距离
	float ward;

	float  act_vel, ex_vel, err, err_vel;
	static float err_sum = 0, last_err = 0;
	static float last_distance = 0;
	float PID_out;

	static uint8_t flag = 0;
	static uint8_t flag_start = 0;

	/* 直线方向计算 */
	ward = RAD_TO_ANGLE((float)atan2(end_posy - pos_y, end_posx - pos_x));
	/* 更新上一次的距离值*/
	last_distance = distance;
	/* 当前距离计算 */
	distance = distanceCal(ward-90 , end_posx, end_posy, pos_x, pos_y);
	
	if (flag_start)
	{
		/* 底盘靠近速度计算 */
		act_vel = (-distance + last_distance)*1.0f/dt;
		/* 减速距离计算 */
		reduce_distance = (float) 0.5*act_vel*act_vel / ACC_MAX;


	}
	else
	{
		flag_start = 1;
		reduce_distance = 0;

	}

	/* 判断终点闭环是否进入 */

    if(!flag)
		if (fabs(distance) <= reduce_distance)
		{
			flag = 1;
			err_sum = 0;
			last_err = 0;
		}
	if (flag)
	{
		/* 期望的速度 */
		ex_vel= (float)sqrt(2 * fabs(distance)*ACC_MAX)*distance/ (float)fabs(distance);

		/* PID控制器输出 */
		err = ex_vel - act_vel;
		err_sum = err_sum + err;
		err_vel = err - last_err;
		last_err = err;

		PID_out = Kp_END*err + Ki_END* err_sum + Kd_END*err_vel;
	
		ex_vel = ex_vel + PID_out;

    
		/* 判断当前状态是否满足停下来 */		
		if (fabs(distance) < END_ERR_ALLOW&&fabs(act_vel) < END_VEL_ALLOW)
		{
				
			speed_out = closeLoopLine(ex_vel, ward, ex_Ang, act_Ang, pos_x, pos_y);//三轮速度不会为0，只有标志位变化
			speed_out.status = SUCCESS;
			
			if(movePointCount < DATASIZE - 1)//防止越界
			{
				if(receiveData[movePointCount+1].x == 0&&
					receiveData[movePointCount+1].y == 4000);//下一位为原始数据，说明路径点已经走完
				else
				{
					movePointCount++;
				}
			}
		//	flag = 0;
		//	flag_start = 0;
			// speed_out.v1 = 0;
			// speed_out.v2 = 0;
			// speed_out.v3 = 0;
			return speed_out;
		}
		/* 不满足停下来的条件 */
		speed_out.status = FAILURE;		
		speed_out = closeLoopLine(ex_vel, ward, ex_Ang, act_Ang, pos_x, pos_y);
		return speed_out;
	}
	/* 未进入减速范围，不进行终点闭环 */
	speed_out.status = FAILURE;
	speed_out = closeLoopLine(vel, ward, ex_Ang, act_Ang, pos_x, pos_y);
	return speed_out;
}
/************************ (C) COPYRIGHT 2016 ACTION *****END OF FILE****/
/*
2016/10/26-2016/10/29

鉴于店家所给例程里建立好了数学模型，我相当部分工作用在攻克这份例程。其中有很多可取之处，也埋了很多坑（怀疑是故意的）。
可取之处：
1、这份例程的输出是三个闭环控制的叠加与嵌套，分别是位置闭环（也包含速度闭环，使运动方向与计算所得直线方向相符，
给一个垂直于运动方向的速度作为调节量）、角度闭环（使运动姿态角与设定姿态角相符，叠加一个旋转速度）、
终点闭环（在终点附近时接近终点时减速度，远离终点时加速度，使停止更平稳，有阻尼）。
运动的分解是通过极坐标分解给三个轮子。我如果按照当时想法自己写的话，
大概思路是：指定一个初始姿态 把三个轮子的速度，分解到世界坐标系的x轴和y轴，若要求运动到一个点，
计算x坐标误差和y坐标误差，用PID计算x和y两个逼近速度，再合成一个总的速度，再分解给三个轮子。
加一个姿态角闭环来保证姿势正确。这么分析的话就只有终点闭环和姿态角闭环，
缺点是没有办法保证平稳速度或说是指定速度运动，后期应该会需要再自己加上。自己写的话大概是思路相近，殊途同归吧。
2、运动控制分为多个函数，高级运动是调用低级运动来实现的。

埋的坑：
1、给定程序的坐标与实际坐标镜像对称，ward=-ward，什么鬼？
2、到达终点时先停一下，再继续按原方向运动，直线方向不是实时变化的。
3、解决掉上一个问题后，到达终点后即停止，此时如果受到干扰，除非超过允许值就不进行调整，不利于精确控制。
4、负加速度设置极大，导致底盘摩擦摩擦。

我的顾虑：负加速度极大且到点即停可能是有道理的，减速距离d=v^2/2a，较大的a可以保证最短时间内到达目标点。
如果真的需要这样的话，可以考虑第一次达到目标点后设置标志位，该标志位置位时，使加速度较小。

取其精华去其糟粕后，底盘运动基本到达了想要的效果，与大一做的风力摆有些类似。

-------------------------------------------------------------------------------------------------------------

2016/10/30

现在底盘工作有一些需要处理的问题：
1、运动控制输出值是为达到目标点而计算出的理想速度。我将这个速度分解后直接赋值给了三个轮子。这是不科学的，
因为电机转速接近但并不等于理想速度。之所以能正确前往目标点，是因为全局定位系统的坐标和角度闭环。
这种闭环调整能基本达到目的，但不能做到有效率的跟随，有可能出现运动开始和结束阶段左右扭的情况。
	解决方法：加入电机转速闭环。后期需要加入电流环。但是目前板子还没画好，
	电流的采集、放大和信息处理的方案还没有仔细研究。
2、缺乏上位机或遥控器的支持，不能做到实时控制。
	解决方法：①我继续完善一下那个上位机，使其能做到触摸屏的效果，甚至画出路径。
		  ②让学弟正在调试一块STM32开发板的触摸屏和2401，考虑使这块开发板充当遥控器。

*/
