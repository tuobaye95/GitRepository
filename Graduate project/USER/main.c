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
  函数名称:GetPowerMag()
  函数功能:计算各次谐波幅值
  参数说明:
  备　　注:先将lBufOutArray分解成实部(X)和虚部(Y)，然后计算幅值(sqrt(X*X+Y*Y)
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
		 lBufMagArray[0] = 0;
 }
  /******************************************************************
  函数名称:quicksort()
  函数功能:快速排序算法
  参数说明:数组排序的边界
  备　　注:
  *******************************************************************/
void quicksort(int left, int right) {
	int i, j, t, temp;
	if(left > right)
		return;
    temp = lBufMagArray[left]; //temp中存储基准数
    i = left;
    j = right;
    while(i != j) { //顺序： 从右边开始找
    	while(lBufMagArray[j] >= temp && i < j)
    		j--;
    	while(lBufMagArray[i] <= temp && i < j)//再找右边的
    		i++;       
    	if(i < j)//交换位置
    	{
    		t = lBufMagArray[i];
    		lBufMagArray[i] = lBufMagArray[j];
    		lBufMagArray[j] = t;
    	}
    }
    //最终将基准数归位
    lBufMagArray[left] = lBufMagArray[i];
    lBufMagArray[i] = temp;
    quicksort(left, i-1);//递归处理左边
    quicksort(i+1, right);//递归处理右边
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
  TIM1_Init(999,719);	 //TIM1_Int_Init(999,719);100Khz的计数频率，计数到1000为10ms
	 
	while(1)
	{
		if(dma_flag == 1)
		{
			printf("DMA产生中断\r\n");
			for(i=0; i<NPT; i++)
			{
				//fx = (((float)WriteBuff[i] * (3.3 / 4096)) - 1.5) *  10000; //AD采样值转化为电压值  放大4096？ 
				
				//lBufInArray[i] = ((signed int)fx) << 16;// 问题就出在这了：lBufInArray数组的数据全为0
				// 原因是 signed short 是16位的 左移16位后就全变成0了   int是32位的
				lBufInArray[i] = WriteBuff[i] << 16; // fft输入数组要求高16位存储实部，低16位存储虚部
			 // printf("\r\n%d  %d\r\n", WriteBuff[i], lBufInArray[i]);
			}
		cr4_fft_1024_stm32(lBufOutArray, lBufInArray, NPT);
		GetPowerMag();
			printf("\r\n幅值：\r\n");
		for(j=0; j<NPT; j++)
		{
			printf("\r\n%d\r\n",
			          WriteBuff[j]); // 输出原始数据
		}
		for(z=0; z<NPT/2; z++)
		{ 
			printf("\r\n%d\r\n", lBufMagArray[z]); // 输出FFT结果
		}
		quicksort(0, NPT/2); //输出前三阶频率值
		
		
		
			dma_flag = 0;
		}
	}
 }

