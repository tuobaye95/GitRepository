#ifndef __DMA_H
#define	__DMA_H	   
#include "sys.h"
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
							    					    

#define ADC_BUFF_LEN	1024
#define ADC1_DR_Address    ((uint32_t)0x4001244C)
extern uint16_t ADC_ConvertedValue[ADC_BUFF_LEN];	
extern uint16_t WriteBuff[ADC_BUFF_LEN]; 
extern u8 dma_flag;

void DMA1_Init(void);
#endif




