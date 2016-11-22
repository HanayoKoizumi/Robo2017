#include "include.h"

/**
 * 以毫秒为单位延时
 * @param ms 延时的毫秒
 */
void SYSTICK_Delay1ms(uint16_t ms)
{
	uint32_t countValue;

	SysTick->LOAD  = 64000 - 1;                 //设置重装数值, 64MHZ时延时1ms
	SysTick->VAL   = 0;	                        //清零计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;	//打开计时器

	do
	{
		countValue = SysTick->CTRL;
		if(countValue & (1 << 16))              //当到1ms是计数减1
		{
			ms--;
		} 	
	}
	while(ms);			                        //等待时间到来

	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//关闭计数器	
}
