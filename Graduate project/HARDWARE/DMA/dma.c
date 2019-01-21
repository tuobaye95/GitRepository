#include "dma.h"
#include "string.h"
#include "led.h"
#include "usart.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//DMA ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/8
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
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
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_Address; //����ַ ADC1
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC_ConvertedValue; // DMA�ڴ��ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC; // ���ݴ��䷽��  ���赽�ڴ�
	DMA_InitStructure.DMA_BufferSize = 2048;// DMA�����С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //�����ַ�̶�
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable; //�ڴ��ַ����
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord; //���������ֳ� ����
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; // �ڴ������ֳ� ����
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular; //ѭ��ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High; //���ȼ���
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable; // ��ֹ�ڴ浽�ڴ�Ĵ���
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);
	
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
	
	/* Enable DMA1 channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);
} 

void DMA1_Channel1_IRQHandler(void)
{
	if(DMA_GetFlagStatus(DMA1_FLAG_TC1)) // ͨ��1������ɱ�־λ
	{
		dma_flag = 1;
		DMA_ClearITPendingBit(DMA1_IT_TC1);
		memcpy(WriteBuff, ADC_ConvertedValue, 2048); // ��DMA�ڴ��ȡ����

	}
}

 

























