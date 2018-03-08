#include "main.h"

pFunction Jump_To_Application;
uint32_t JumpAddress;


static uint32_t sysTickUptime = 0;
static volatile uint32_t sysTickCycleCounter = 0;
static volatile uint32_t usTicks = 0;
uint16_t frameCounter = 0;
time_flag TIME_FLAG;

void SysTick_Handler(void)
{
	sysTickCycleCounter = *DWT_CYCCNT;
   	sysTickUptime++;
	frameCounter++;
    if (frameCounter > FRAME_COUNT)
    {
    	frameCounter = 1;
	}
	if ((frameCounter % COUNT_500HZ) == 0)
	{
		TIME_FLAG.time_sub.flag_500hz=TRUE;
	}
	if ((frameCounter % COUNT_100HZ) == 0)
	{
		TIME_FLAG.time_sub.flag_100hz=TRUE;
	}
	if ((frameCounter % COUNT_50HZ) == 0)
	{
		TIME_FLAG.time_sub.flag_50hz=TRUE;
	}
	if ((frameCounter % COUNT_10HZ) == 0)
	{
		TIME_FLAG.time_sub.flag_10hz=TRUE;
	}
	if ((frameCounter % COUNT_5HZ) == 0)
	{
		TIME_FLAG.time_sub.flag_5hz=TRUE;
	}
	if ((frameCounter % COUNT_2HZ) == 0)
	{
		TIME_FLAG.time_sub.flag_2hz=TRUE;
	}
	if ((frameCounter % COUNT_1HZ) == 0)
	{
		TIME_FLAG.time_sub.flag_1hz=TRUE;
	}
	if ((frameCounter % COUNT_0_5HZ) == 0)
	{
		TIME_FLAG.time_sub.flag_0_5hz=TRUE;
	}
}
/*******************************************************************************
函 数 名：void Boot_Flash_ErasePage(void)
功能描述： 擦除flash
入口参数：	无
返回参数：无
创建时间: 2018-01-24 by zam
********************************************************************************/
 void Boot_Flash_ErasePage()
 {
		uint32_t NbrOfPage;
		uint32_t EraseCounter;
		FLASH_Status FLASHStatus = FLASH_COMPLETE;
		FLASH_UnlockBank1();
	  	NbrOfPage = FLASH_IMAGE_SIZE / PAGE_SIZE;
	  	FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);
		for(EraseCounter = 0; (EraseCounter < NbrOfPage) && (FLASHStatus == FLASH_COMPLETE); EraseCounter++)
		{
			FLASHStatus = FLASH_ErasePage(ApplicationAddress + (PAGE_SIZE * EraseCounter));
		}
		FLASH_LockBank1();
 }
uint32_t boot_Address=ApplicationAddress;

void Date_Program(unsigned char *date)
{
	unsigned int date_count=0;
	unsigned int i=0;
	unsigned char check_sum=0;
	unsigned char Date_State[6];
	unsigned char aa;
	uint16_t RamSource;
	memcpy(&Date_State[0],&date[0],4);
	
	if((date[0]==DATE_HEAD0)&&(date[1]==DATE_HEAD1))
	{
		date_count=(date[2]<<8)+date[3];
	}
	for(i=0;i<date_count;i++)
	{
		check_sum+=date[4+i];
	}
	if(check_sum==date[4+date_count])
	{
		Send_Data_Byte(USART1,&date[4],date_count);
		FLASH_UnlockBank1();
		date_count/=2;
		for(i=0;i<date_count;i++)
		{
			//RamSource=((uint16_t)date[4+i*2]<<8)+date[5+i*2];
			RamSource=((uint16_t)date[5+i*2]<<8)+date[4+i*2];
			while(FLASH_ProgramHalfWord(boot_Address,RamSource)!=FLASH_COMPLETE);
			//aa=FLASH_ProgramOptionByteData(boot_Address,date[4+i]);
			boot_Address+=2;
		}
			FLASH_LockBank1();
		Date_State[4]=0x0F;
		Date_State[5]=0x0F;
	}
	else
	{	
		Date_State[4]=0xF0;
		Date_State[5]=0xF0;
	}
	Send_Data_Byte(USART2,&Date_State[0],6);
	//printf("cnd=%d\r\n",date_count);
}
int main()
{
	unsigned char boot_time=0;
	unsigned int boot_len=0;
	unsigned int	boot_cnt=0;
	SystemInit();
	SysTick_Config(SystemCoreClock / 1000);
	Usart_init();
	LED_Init();
	Ble_Bluetooth_Init();
	while(1)
	{
		if(TIME_FLAG.time_sub.flag_1hz)
		{
			TIME_FLAG.time_sub.flag_1hz=FALSE;
			LED_STATU_ON_OFF;
			boot_time++;
			if(boot_time>20)
			{
				break;
			}
		}
		if(BOOT_USART.receve_ok)
		{
			if((strstr(&BOOT_USART.messg_buff[0],"boot"))!=NULL)
			{
				///FLASH_Unlock();
				BOOT_USART.receve_ok=FALSE;
				Boot_Flash_ErasePage();
				printf("---enter boot model......\r\n");
				USART_ClearFlag(USART1,USART_FLAG_TC);
				USART_ClearFlag(USART2,USART_FLAG_TC);
				while(1)
				{
					if(BOOT_USART.receve_ok)
					{
						if((strstr(&BOOT_USART.messg_buff[0],"OK"))!=NULL)
						{
							FLASH_LockBank1();
							BOOT_USART.receve_ok=FALSE;
							break;
						}
						else
						{
							Date_Program(&BOOT_USART.messg_buff[0]);
							//boot_cnt++;
							//printf("---enter boot times......%d\r\n",boot_cnt);
						}
						BOOT_USART.receve_ok=FALSE;
					}
					
				}
			}
			//Send_Data_Byte(USART1,&USART2_MESSG.messg_buff[0],USART2_MESSG.date_lenth);
			//UART_SendString(BLUETOOTH_USART,&USART2_MESSG.messg_buff[0]);
			USART2_MESSG.receve_ok=FALSE;
		}
	}
	if (((*(__IO uint32_t*)ApplicationAddress) & 0x2FFE0000 ) == 0x20000000)
    { 
      /* Jump to user application */
      JumpAddress = *(__IO uint32_t*) (ApplicationAddress + 4);
      Jump_To_Application = (pFunction) JumpAddress;
      /* Initialize user application's Stack Pointer */
      __set_MSP(*(__IO uint32_t*) ApplicationAddress);
  	 	Jump_To_Application();
    }
	while(1)
	{
		
	}
}
