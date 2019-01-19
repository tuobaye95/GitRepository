#ifndef __MAIN_H
#define __MAIN_H

typedef unsigned char  uint8;                   /* 无符号8位整型变量                        */
typedef signed   char  int8;                    /* 有符号8位整型变量                        */
typedef unsigned short uint16;                  /* 无符号16位整型变量                       */
typedef signed   short int16;                   /* 有符号16位整型变量                       */
typedef unsigned long   uint32;                  /* 无符号32位整型变量                       */
typedef signed   long   int32;                   /* 有符号32位整型变量                       */
typedef float          fp32;                    /* 单精度浮点数（32位长度）                 */
typedef double         fp64;                    /* 双精度浮点数（64位长度） 				*/

#include "stm32f10x.h"
#include "stdio.h"
#include "usart.h"
#include "delay.h"
#include "sys.h"
#include "stm32f10x_it.h"
#include "math.h"
#include "timer.h"
#include "adc.h"

#endif
