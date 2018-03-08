/*
 * File      : main.h
 * This file is ef comp
 * COPYRIGHT (C) 2017,
 *ZA
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at my addr
 * Change Logs:
 * Date           Author       ZAM
 * 2017-09-26     Bernard      the first version
 */
 #ifndef MAIN__H
 #define MAIN__H
 
 #include "stm32f10x.h"
#include "usart.h"
#include "led.h"
#include "bluetooth.h"


 typedef  void (*pFunction)(void);
  extern pFunction Jump_To_Application;
  
 #define CMD_STRING_SIZE       256
 #define ApplicationAddress    0x8004000

 #define PAGE_SIZE                         (0x800)    /* 2 Kbytes */
 #define FLASH_SIZE                        (0x3C000)  /* 256 KBytes */
 #define FLASH_IMAGE_SIZE                   (uint32_t) (FLASH_SIZE - (ApplicationAddress - 0x08000000))


#define FALSE 0
#define TRUE  1

#define DATE_HEAD0 0xFE
#define DATE_HEAD1 0x01

#define BOOT_USART USART2_MESSG

#define FRAME_COUNT   2000
 
#define COUNT_500HZ   2         // Number of 1000 Hz frames for 500 Hz Loop
#define COUNT_100HZ   10        // Number of 1000 Hz frames for 100 Hz Loop
#define COUNT_50HZ    20        // Number of 1000 Hz frames for  50 Hz Loop
#define COUNT_10HZ    100       // Number of 1000 Hz frames for  10 Hz Loop
#define COUNT_5HZ     200       // Number of 1000 Hz frames for   5 Hz Loop
#define COUNT_2HZ     500       // Number of 1000 Hz frames for   5 Hz Loop
#define COUNT_1HZ     1000      // Number of 1000 Hz frames for   1 Hz Loop
#define COUNT_0_5HZ     2000      // Number of 1000 Hz frames for   1 Hz Loop
#define DWT_CTRL    (*(volatile uint32_t *)0xE0001000)
#define DWT_CYCCNT  ((volatile uint32_t *)0xE0001004)
#define CYCCNTENA   (1 << 0)
 typedef union
{ 
	unsigned char time_all;
  struct
	{
		unsigned flag_500hz;
		unsigned flag_100hz;
		unsigned flag_50hz;
		unsigned flag_10hz;
		unsigned flag_5hz;
		unsigned flag_2hz;
		unsigned flag_1hz;
		unsigned flag_0_5hz;
	}time_sub;
}time_flag;
 #endif
 
 
