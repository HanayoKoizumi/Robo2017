#include "include.h"


uint16StructTypeDef receiveData[DATASIZE];//保存接受数据的结构体数组

/**
 * 接收初始化
 */
void ReceiveInit(void)
{
	UART3_Init();
	ClearReceiveData();//将每一点设为原点
}


/*************清除数据*******************/
void ClearReceiveData(void)
{
	uint8_t i;
    for(i = 0; i < DATASIZE ; i++)
    {
		receiveData[i].x = 0;
		receiveData[i].y = 4000;
    }
   	//receiveData[0].x = 0 , receiveData[0].y = 4000;//运动原点
} 

