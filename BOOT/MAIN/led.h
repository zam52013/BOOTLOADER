/*
 * File      : led.h
 * This file is ef comp
 * COPYRIGHT (C) 2017,
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 *
 *
 * Change Logs:
 * Date           Author       ZAM
 * 2017-09-26     Bernard      the first version
 */


#ifndef __LED_H_
#define __LED_H_

#include "stm32f10x.h"

/*********定位状态指示灯******************/
#define LED_STATU_PORT GPIOB
#define LED_STATU_RCC RCC_APB2Periph_GPIOB
#define LED_STATU_GPIO GPIO_Pin_2
#define LED_STATU_ON_OFF  GPIO_WriteBit(LED_STATU_PORT,LED_STATU_GPIO,(BitAction)!GPIO_ReadOutputDataBit(LED_STATU_PORT,LED_STATU_GPIO))
#define LED_STATU_OFF  GPIO_ResetBits(LED_STATU_PORT,LED_STATU_GPIO)			//电源状态指示灯
#define LED_STATU_ON GPIO_SetBits(LED_STATU_PORT,LED_STATU_GPIO)			//电源状态指示灯
/***************************/
void LED_Init(void);//初始化

		 				    
#endif


