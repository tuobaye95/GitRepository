#ifndef __DMA_H
#define	__DMA_H	   
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//DMA 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/8
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
							    					    

#define ADC_BUFF_LEN	1024
#define ADC1_DR_Address    ((uint32_t)0x4001244C)
extern uint16_t ADC_ConvertedValue[ADC_BUFF_LEN];	
extern uint16_t WriteBuff[ADC_BUFF_LEN]; 
extern u8 dma_flag;

void DMA1_Init(void);
#endif




