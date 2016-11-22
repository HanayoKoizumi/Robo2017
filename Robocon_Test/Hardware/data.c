#include "include.h"


uint16StructTypeDef receiveData[DATASIZE];//保存接受数据的结构体数组

/**
 * 接收初始化
 */
void ReceiveInit(void)
{
	SPI_NRF_Init();
	//检测2401是否连接
	NRF_RX_Mode();//接受模式
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


/*****************接收**********************/
void ReceiveData(void)
{

	uint8_t receive_buff[4];//接收缓冲
	uint8_t status;
	static uint8_t j = 1;//接收数据从第二位开始，第一位恒为原点

	status = NRF_Rx_Dat(receive_buff);

	if(status == RX_DR)//接受成功
	{
		if((receive_buff[0] == 0x00)&&(receive_buff[1] == 0x00)&&
			(receive_buff[2] == 0x00)&&(receive_buff[3] == 0x00))//重置信号
		{
			ClearReceiveData();
			j = 1;
			point_count = 0;//收到重置信号回到原点
		}
		else
		{
		//	SMG_Display(6);
			if(j < DATASIZE)//可以收到数据,接收数组没有越界，
			{

				receiveData[j].x = ((uint16_t)receive_buff[0] << 8)|(uint16_t)receive_buff[1];//转换数据
				receiveData[j].y = ((uint16_t)receive_buff[2] << 8)|(uint16_t)receive_buff[3];

				j++;
			}//如果超出容量则舍弃数据
		}
	}
}



