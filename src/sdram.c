#include "sdram.h"


void SDRAM_timeout() {
	uint32_t sdram_conf_timeout = SDRAM_TIMEOUT;
		while(sdram_conf_timeout > 0) sdram_conf_timeout--;
}

void FMC_init() {
	FMC_SDRAMCommandTypeDef		FMC_command;
	FMC_SDRAMTimingInitTypeDef 	FMC_timing;
	FMC_SDRAMInitTypeDef		FMC_init;

	uint32_t sdram_conf_timeout = SDRAM_TIMEOUT;
	uint32_t systemCoreClock_div2 = SystemCoreClock / 2;
	float clock_ghz = systemCoreClock_div2/1000000;
	double tick = 1/clock_ghz*1000; // ns

	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FMC, ENABLE);

	FMC_timing.FMC_LoadToActiveDelay	= 2;
	FMC_timing.FMC_ExitSelfRefreshDelay = ceil(70/tick);
	FMC_timing.FMC_SelfRefreshTime		= ceil(42/tick);
	FMC_timing.FMC_RowCycleDelay		= ceil(70/tick);
	FMC_timing.FMC_WriteRecoveryTime	= 1 + ceil(7/tick);
	FMC_timing.FMC_RPDelay				= ceil(20/tick);
	FMC_timing.FMC_RCDDelay				= ceil(20/tick);

	FMC_init.FMC_Bank				= FMC_Bank2_SDRAM;
	FMC_init.FMC_ColumnBitsNumber	= FMC_ColumnBits_Number_8b;
	FMC_init.FMC_RowBitsNumber		= FMC_RowBits_Number_12b;
	FMC_init.FMC_InternalBankNumber = FMC_InternalBank_Number_4;
	FMC_init.FMC_SDMemoryDataWidth	= FMC_SDMemory_Width_16b;
	FMC_init.FMC_CASLatency			= FMC_CAS_Latency_3;
	FMC_init.FMC_WriteProtection	= FMC_Write_Protection_Disable;
	FMC_init.FMC_SDClockPeriod		= FMC_SDClock_Period_2;
	FMC_init.FMC_ReadBurst			= FMC_Read_Burst_Disable;
	FMC_init.FMC_ReadPipeDelay		= FMC_ReadPipe_Delay_1;
	FMC_init.FMC_SDRAMTimingStruct  = &FMC_timing;

	FMC_SDRAMInit(&FMC_init);

	FMC_command.FMC_CommandMode 			= FMC_Command_Mode_CLK_Enabled;
	FMC_command.FMC_CommandTarget			= FMC_Command_Target_bank2;
	FMC_command.FMC_ModeRegisterDefinition 	= 0;
	FMC_command.FMC_AutoRefreshNumber		= 1;

	SDRAM_timeout();

	FMC_SDRAMCmdConfig(&FMC_command);

	// TODO: Change this to delay function
	uint32_t delay = 1000000;
	while(delay > 0) delay--;

	FMC_command.FMC_CommandMode 			= FMC_Command_Mode_PALL;
	FMC_command.FMC_CommandTarget 			= FMC_Command_Target_bank2;
	FMC_command.FMC_AutoRefreshNumber 		= 1;
	FMC_command.FMC_ModeRegisterDefinition 	= 0;

	SDRAM_timeout();

	FMC_SDRAMCmdConfig(&FMC_command);

	FMC_command.FMC_CommandMode 			= FMC_Command_Mode_AutoRefresh;
	FMC_command.FMC_CommandTarget			= FMC_Command_Target_bank2;
	FMC_command.FMC_AutoRefreshNumber		= 8;
	FMC_command.FMC_ModeRegisterDefinition  = 0;

	SDRAM_timeout();

	FMC_SDRAMCmdConfig(&FMC_command);

	FMC_command.FMC_CommandMode 			= FMC_Command_Mode_LoadMode;
	FMC_command.FMC_CommandTarget 			= FMC_Command_Target_bank2;
	FMC_command.FMC_AutoRefreshNumber		= 1;
	FMC_command.FMC_ModeRegisterDefinition	= (uint32_t)0x0231;


	SDRAM_timeout();
	FMC_SDRAMCmdConfig(&FMC_command);


	FMC_SetRefreshCount(680);
}

void GPIO_FMC_init() {
	GPIO_InitTypeDef		gpio_init;

	RCC_AHB1PeriphClockCmd(
			  RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC
			| RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOE
			| RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG, ENABLE);

	gpio_init.GPIO_Mode = GPIO_Mode_AF;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init.GPIO_OType = GPIO_OType_PP;
	gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource5, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_FMC);
	gpio_init.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_Init(GPIOB, &gpio_init);

	GPIO_PinAFConfig(GPIOC, GPIO_PinSource0, GPIO_AF_FMC);
	gpio_init.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init(GPIOC, &gpio_init);

	GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource10, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_FMC);
	gpio_init.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1  | GPIO_Pin_8  |
				GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 |
				GPIO_Pin_15;
	GPIO_Init(GPIOD, &gpio_init);

	GPIO_PinAFConfig(GPIOE, GPIO_PinSource0, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource1, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource7, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource8, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource9, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource10, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource11, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource12, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource13, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource14, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOE, GPIO_PinSource15, GPIO_AF_FMC);
	gpio_init.GPIO_Pin = GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_7  |
				GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 |
				GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 |
				GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOE, &gpio_init);

	GPIO_PinAFConfig(GPIOF, GPIO_PinSource0, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource1, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource2, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource3, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource4, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource5, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource11, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource12, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource13, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource14, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource15, GPIO_AF_FMC);
	gpio_init.GPIO_Pin = GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_2  |
				GPIO_Pin_3  | GPIO_Pin_4  | GPIO_Pin_5  |
				GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 |
				GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_Init(GPIOF, &gpio_init);

	GPIO_PinAFConfig(GPIOG, GPIO_PinSource0, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource1, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource4, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource5, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource8, GPIO_AF_FMC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource15, GPIO_AF_FMC);
	gpio_init.GPIO_Pin = GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_4  |
				GPIO_Pin_5  | GPIO_Pin_8  | GPIO_Pin_15;
	GPIO_Init(GPIOG, &gpio_init);
}

void SDRAM_WriteBuffer(uint16_t* pBuffer, uint16_t uwWriteAddress, uint16_t uwBufferSize)
 {
   __IO uint16_t write_pointer = (uint16_t)uwWriteAddress;

   FMC_SDRAMWriteProtectionConfig(FMC_Bank2_SDRAM, DISABLE);
   while(FMC_GetFlagStatus(FMC_Bank2_SDRAM, FMC_FLAG_Busy) != RESET)
   {
   }
   for (; uwBufferSize != 0; uwBufferSize--)
   {
     *(uint16_t *) (SDRAM_START_ADDRESS + write_pointer) = *pBuffer++;
     write_pointer += 2;
   }
 }
