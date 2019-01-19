#include "main.h"
#include "stm32_dsp.h"
#include "table_fft.h"
#include "adc.h"
#include "dma.h"
#include "timer.h"
#include "usart.h"
#include "delay.h"
#include "sys.h"
#include "led.h"


#define PI2  6.28318530717959
#define Fs  100
#define NPT 1024

u32 lBufInArray[NPT];
u32 lBufOutArray[NPT];
u32 lBufMagArray[NPT];

uint16 NPT_num=0;

uint16 Time_us_count=0;
uint16 Time_ms_count=0;
uint8 start_falg=0;

void GetPowerMag(void);
 /******************************************************************
  ��������:GetPowerMag()
  ��������:�������г����ֵ
  ����˵��:
  ������ע:�Ƚ�lBufOutArray�ֽ��ʵ��(X)���鲿(Y)��Ȼ������ֵ(sqrt(X*X+Y*Y)
  *******************************************************************/
 void GetPowerMag(void)
 {
     s16 lX,lY;
     float X,Y,Mag;
     u16 i;
     for(i=0; i<NPT/2; i++)
     {
         lX  = (lBufOutArray[i] << 16) >> 16;
         lY  = (lBufOutArray[i] >> 16);
			   //printf("\r\n%d\r\n", lX);
         X = NPT * ((float)lX) / 32768;
         Y = NPT * ((float)lY) / 32768;
         Mag = sqrt(X * X + Y * Y) / NPT;
         if(i == 0)
             lBufMagArray[i] = (u32)(Mag * 32768);
         else
             lBufMagArray[i] = (u32)(Mag * 65536);
     }
 }
 int main(void)
 {	
  uint16 i, j, z; 
  float fx;
  SystemInit();
  uart_init(115200);
  delay_init();
  Adc_Init(); 
	DMA1_Init();
  TIM1_Init(999,719);	 //TIM1_Int_Init(999,719);100Khz�ļ���Ƶ�ʣ�������1000Ϊ10ms
	 
	while(1)
	{
		if(dma_flag == 1)
		{
			printf("DMA�����ж�\r\n");
			for(i=0; i<NPT; i++)
			{
				//fx = (((float)WriteBuff[i] * (3.3 / 4096)) - 1.5) *  10000; //AD����ֵת��Ϊ��ѹֵ  �Ŵ�4096�� 
				
				//lBufInArray[i] = ((signed int)fx) << 16;// ����ͳ������ˣ�lBufInArray���������ȫΪ0
				// ԭ���� signed short ��16λ�� ����16λ���ȫ���0��   int��32λ��
				lBufInArray[i] = WriteBuff[i] << 16; // fft��������Ҫ���16λ�洢ʵ������16λ�洢�鲿
			 // printf("\r\n%d  %d\r\n", WriteBuff[i], lBufInArray[i]);
			}
		cr4_fft_1024_stm32(lBufOutArray, lBufInArray, NPT);
		GetPowerMag();
			printf("\r\n��ֵ��\r\n");
		for(j=0; j<NPT; j++)
		{
			//printf("\r\n%d\r\n", WriteBuff[j], Value[j], lBufInArray[j]);
			printf("\r\n%d\r\n",
			          WriteBuff[j]);
		}
//		for(j=0; j<NPT/2; j++)
//		{
//			printf("\r\n%d\r\n", lBufOutArray[j]);
//		}
		for(z=0; z<NPT/2; z++)
		{ 
			printf("\r\n%d\r\n", lBufMagArray[z]);
		}
		
			dma_flag = 0;
		}
	}
 }

