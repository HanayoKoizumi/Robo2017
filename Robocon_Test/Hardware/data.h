#ifndef __DATA__H
#define __DATA__H

#define DATASIZE 100//数组长度

//发送接受处理的结构体定义

typedef struct data
{
	uint16_t x;
	uint16_t y;
}uint16StructTypeDef;

typedef struct 
{
	uint8_t xhigh;
	uint8_t xlow;
	uint8_t yhigh;
	uint8_t ylow;
}uint8StructTypeDef;

// typedef union
// {
// 	uint8_t uint8X[2];
// 	uint16_t uint16X;
// }unionX;

// typedef union
// {
// 	uint8_t uint8Y[2];
// 	uint16_t uint16Y;
// }unionY;


void ClearReceiveData(void);
void ReceiveData(void);
void ReceiveInit(void);
void ReceiveTest(void);


extern uint16StructTypeDef receiveData[DATASIZE];


#endif
