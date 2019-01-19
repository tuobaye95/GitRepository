#include "dma.h"
#include "string.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
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

uint16_t ADC_ConvertedValue[ADC_BUFF_LEN];
uint16_t WriteBuff[ADC_BUFF_LEN]; 
u8 dma_flag = 0;


void DMA1_Init(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
 
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* DMA1 Channel1 Configuration ----------------------------------------------*/
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address; //基地址 ADC1
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_ConvertedValue; // DMA内存地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; // 数据传输方向  外设到内存
	DMA_InitStructure.DMA_BufferSize = 2048;// DMA缓存大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址固定
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //内存地址递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //外设数据字长 半字
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; // 内存数据字长 半字
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //循环模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //优先级高
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; // 禁止内存到内存的传输
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
	
	/* Enable DMA1 channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);
} 

void DMA1_Channel1_IRQHandler(void)
{
	if(DMA_GetFlagStatus(DMA1_FLAG_TC1)) // 通道1传输完成标志位
	{
		dma_flag = 1;
		DMA_ClearITPendingBit(DMA1_IT_TC1);
		memcpy(WriteBuff, ADC_ConvertedValue, 2048); // 从DMA内存获取数据

	}
}

 

























