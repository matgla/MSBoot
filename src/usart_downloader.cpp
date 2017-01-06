#include <stm32f4xx_flash.h>

#include "usart_downloader.hpp"

using usart = hw::USART<hw::USARTS::USART1_PP1>;

UsartDownloader::UsartDownloader(const Logger& logger) : logger_(logger) 
{

}

#define FLASH_WRP_SECTORS   (OB_WRP_Sector_1) /* sectors 2 and 3  */


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define FLASH_USER_START_ADDR   ADDR_FLASH_SECTOR_4   /* Start address of user Flash area */

#if defined (USE_STM324xG_EVAL)
#define FLASH_USER_END_ADDR     ADDR_FLASH_SECTOR_11  /* End address of user Flash area */

#else /* USE_STM324x7I_EVAL or USE_STM324x9I_EVAL */
#define FLASH_USER_END_ADDR     ADDR_FLASH_SECTOR_23  /* End address of user Flash area */
#endif 

/* Base address of the Flash sectors */ 
#define ADDR_FLASH_SECTOR_0     ((uint32_t)0x08000000) /* Base address of Sector 0, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_1     ((uint32_t)0x08004000) /* Base address of Sector 1, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_2     ((uint32_t)0x08008000) /* Base address of Sector 2, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_3     ((uint32_t)0x0800C000) /* Base address of Sector 3, 16 Kbytes   */
#define ADDR_FLASH_SECTOR_4     ((uint32_t)0x08010000) /* Base address of Sector 4, 64 Kbytes   */
#define ADDR_FLASH_SECTOR_5     ((uint32_t)0x08020000) /* Base address of Sector 5, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_6     ((uint32_t)0x08040000) /* Base address of Sector 6, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_7     ((uint32_t)0x08060000) /* Base address of Sector 7, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_8     ((uint32_t)0x08080000) /* Base address of Sector 8, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_9     ((uint32_t)0x080A0000) /* Base address of Sector 9, 128 Kbytes  */
#define ADDR_FLASH_SECTOR_10    ((uint32_t)0x080C0000) /* Base address of Sector 10, 128 Kbytes */
#define ADDR_FLASH_SECTOR_11    ((uint32_t)0x080E0000) /* Base address of Sector 11, 128 Kbytes */

#define ADDR_FLASH_SECTOR_12     ((uint32_t)0x08100000) /* Base address of Sector 12, 16 Kbytes  */
#define ADDR_FLASH_SECTOR_13     ((uint32_t)0x08104000) /* Base address of Sector 13, 16 Kbytes  */
#define ADDR_FLASH_SECTOR_14     ((uint32_t)0x08108000) /* Base address of Sector 14, 16 Kbytes  */
#define ADDR_FLASH_SECTOR_15     ((uint32_t)0x0810C000) /* Base address of Sector 15, 16 Kbytes  */
#define ADDR_FLASH_SECTOR_16     ((uint32_t)0x08110000) /* Base address of Sector 16, 64 Kbytes  */
#define ADDR_FLASH_SECTOR_17     ((uint32_t)0x08120000) /* Base address of Sector 17, 128 Kbytes */
#define ADDR_FLASH_SECTOR_18     ((uint32_t)0x08140000) /* Base address of Sector 18, 128 Kbytes */
#define ADDR_FLASH_SECTOR_19     ((uint32_t)0x08160000) /* Base address of Sector 19, 128 Kbytes */
#define ADDR_FLASH_SECTOR_20     ((uint32_t)0x08180000) /* Base address of Sector 20, 128 Kbytes */
#define ADDR_FLASH_SECTOR_21     ((uint32_t)0x081A0000) /* Base address of Sector 21, 128 Kbytes */
#define ADDR_FLASH_SECTOR_22     ((uint32_t)0x081C0000) /* Base address of Sector 22, 128 Kbytes */
#define ADDR_FLASH_SECTOR_23     ((uint32_t)0x081E0000) /* Base address of Sector 23, 128 Kbytes */

#define DATA_32                 ((uint32_t)0x12345678)

uint32_t uwStartSector = 0;
uint32_t uwEndSector = 0;
uint32_t uwAddress = 0;
uint32_t uwSectorCounter = 0;

__IO uint32_t uwData32 = 0;
__IO uint32_t uwMemoryProgramStatus = 0;

static uint32_t GetSector(uint32_t Address)
{
  uint32_t sector = 0;
  
  if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
  {
    sector = FLASH_Sector_0;  
  }
  else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
  {
    sector = FLASH_Sector_1;  
  }
  else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
  {
    sector = FLASH_Sector_2;  
  }
  else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
  {
    sector = FLASH_Sector_3;  
  }
  else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
  {
    sector = FLASH_Sector_4;  
  }
  else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
  {
    sector = FLASH_Sector_5;  
  }
  else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
  {
    sector = FLASH_Sector_6;  
  }
  else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
  {
    sector = FLASH_Sector_7;  
  }
  else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
  {
    sector = FLASH_Sector_8;  
  }
  else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
  {
    sector = FLASH_Sector_9;  
  }
  else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
  {
    sector = FLASH_Sector_10;  
  }
  
#if defined (USE_STM324xG_EVAL)
  else/*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_11))*/
  {
    sector = FLASH_Sector_11;  
  }

#else /* USE_STM324x7I_EVAL or USE_STM324x9I_EVAL */  
  else if((Address < ADDR_FLASH_SECTOR_12) && (Address >= ADDR_FLASH_SECTOR_11))
  {
    sector = FLASH_Sector_11;  
  }

  else if((Address < ADDR_FLASH_SECTOR_13) && (Address >= ADDR_FLASH_SECTOR_12))
  {
    sector = FLASH_Sector_12;  
  }
  else if((Address < ADDR_FLASH_SECTOR_14) && (Address >= ADDR_FLASH_SECTOR_13))
  {
    sector = FLASH_Sector_13;  
  }
  else if((Address < ADDR_FLASH_SECTOR_15) && (Address >= ADDR_FLASH_SECTOR_14))
  {
    sector = FLASH_Sector_14;  
  }
  else if((Address < ADDR_FLASH_SECTOR_16) && (Address >= ADDR_FLASH_SECTOR_15))
  {
    sector = FLASH_Sector_15;  
  }
  else if((Address < ADDR_FLASH_SECTOR_17) && (Address >= ADDR_FLASH_SECTOR_16))
  {
    sector = FLASH_Sector_16;  
  }
  else if((Address < ADDR_FLASH_SECTOR_18) && (Address >= ADDR_FLASH_SECTOR_17))
  {
    sector = FLASH_Sector_17;  
  }
  else if((Address < ADDR_FLASH_SECTOR_19) && (Address >= ADDR_FLASH_SECTOR_18))
  {
    sector = FLASH_Sector_18;  
  }
  else if((Address < ADDR_FLASH_SECTOR_20) && (Address >= ADDR_FLASH_SECTOR_19))
  {
    sector = FLASH_Sector_19;  
  }
  else if((Address < ADDR_FLASH_SECTOR_21) && (Address >= ADDR_FLASH_SECTOR_20))
  {
    sector = FLASH_Sector_20;  
  } 
  else if((Address < ADDR_FLASH_SECTOR_22) && (Address >= ADDR_FLASH_SECTOR_21))
  {
    sector = FLASH_Sector_21;  
  }
  else if((Address < ADDR_FLASH_SECTOR_23) && (Address >= ADDR_FLASH_SECTOR_22))
  {
    sector = FLASH_Sector_22;  
  }
  else/*(Address < FLASH_END_ADDR) && (Address >= ADDR_FLASH_SECTOR_23))*/
  {
    sector = FLASH_Sector_23;  
  }
#endif /* USE_STM324x7I_EVAL or USE_STM324x9I_EVAL */
  return sector;
}


void UsartDownloader::writeToMemory()
{
    FLASH_Unlock();
    
  /* Erase the user Flash area ************************************************/
  /* area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR */

  /* Clear pending flags (if any) */  
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
                  FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR); 

  /* Get the number of the start and end sectors */
  uwStartSector = GetSector(FLASH_USER_START_ADDR);
  uwEndSector = GetSector(FLASH_USER_END_ADDR);

  /* Strat the erase operation */
  uwSectorCounter = uwStartSector;
  while (uwSectorCounter <= uwEndSector) 
  {
    /* Device voltage range supposed to be [2.7V to 3.6V], the operation will
       be done by word */ 
    if (FLASH_EraseSector(uwSectorCounter, VoltageRange_3) != FLASH_COMPLETE)
    { 
      /* Error occurred while sector erase. 
         User can add here some code to deal with this error  */
         logger_ << Level::ERROR << "Ereasing failed \r\n";
      while (1)
      {
      }
    }
    /* jump to the next sector */
    if (uwSectorCounter == FLASH_Sector_11)
    {
      uwSectorCounter += 40;
    } 
    else 
    {
      uwSectorCounter += 8;
    }
  }

  /* Program the user Flash area word by word ********************************/
  /* area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR */

  uwAddress = FLASH_USER_START_ADDR;

  while (uwAddress < FLASH_USER_END_ADDR)
  {
    if (FLASH_ProgramWord(uwAddress, DATA_32) == FLASH_COMPLETE)
    {
      uwAddress = uwAddress + 4;
    }
    else
    { 
      /* Error occurred while writing data in Flash memory. 
         User can add here some code to deal with this error */
         logger_ << Level::ERROR << "Writing failed \r\n";
      while (1)
      {
      }
    }
  }

  /* Lock the Flash to disable the flash control register access (recommended
     to protect the FLASH memory against possible unwanted operation) */
  FLASH_Lock(); 


  /* Check if the programmed data is OK ***************************************/
  /*  MemoryProgramStatus = 0: data programmed correctly
      MemoryProgramStatus != 0: number of words not programmed correctly */
  uwAddress = FLASH_USER_START_ADDR;
  uwMemoryProgramStatus = 0;
  
  while (uwAddress < FLASH_USER_END_ADDR)
  {
    uwData32 = *(__IO uint32_t*)uwAddress;

    if (uwData32 != DATA_32)
    {
      uwMemoryProgramStatus++;  
    }

    uwAddress = uwAddress + 4;
  }  
 
  /* Check Data correctness */
  if(uwMemoryProgramStatus)
  {
    /* KO */
    /* Turn on LD2 */
    logger_ << Level::ERROR << "Success \r\n";
  }
  else
  {
    /* OK */
    /* Turn on LD1 */
    logger_ << Level::ERROR << " failed \r\n";
    //STM_EVAL_LEDOn(LED1);    
  }


    // logger_ << Level::INFO << "Waiting for soft\n";
    // u32 softwareSize = 0;
    // usart::getUsart().send(10, 2);
    // auto msg = usart::getUsart().getMessage();
    // logger_ << Level::INFO << "Received message: " << msg.payload[0] << ":" << msg.payload[1] << ":" << msg.payload[2] << ":" << msg.payload[3] << ":"  << "\r\n";
    // softwareSize = msg.payload[0] << 12;
    // softwareSize += msg.payload[1] << 8;
    // softwareSize += msg.payload[2] << 4;
    // softwareSize += msg.payload[3];
    // logger_ << Level::INFO << "Received soft size: " << softwareSize << "\r\n";

    // u32 receivedSize = 0;
    // while (receivedSize < softwareSize)
    // {
    //     usart::getUsart().send(10, 3);
    //     auto msg1 = usart::getUsart().getMessage();
    //     logger_ << Level::INFO << "Received block of data of size: " << msg1.size << "\r\n";
    //     //FLASH_Unlock();
    //     // //Unlock Flash
    //     // FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR | 
    //     //           FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);

    //     // FLASH->CR = FLASH_CR_LOCK;
    //     // if( FLASH->CR & FLASH_CR_LOCK ){
    //     // // Unlock fpec                
    //     // FLASH->OPTKEYR = 0x45670123;
    //     // FLASH->OPTKEYR = 0xCDEF89AB;
    //     // } else 
    //     // {
    //     //     logger_ << Level::INFO << "Error unlickonk\r\n";
    //     // }

    //     // FLASH->CR = FLASH_CR_LOCK; 
    //     // if( FLASH->CR & FLASH_CR_LOCK ){
    //     // // Unlock fpec   
    //     //     FLASH->KEYR = 0x45670123;
    //     //     FLASH->KEYR = 0xCDEF89AB;
    //     //     FLASH->OPTKEYR = 0x45670123;
    //     //     FLASH->OPTKEYR = 0xCDEF89AB;
    //     // } 
    //     // else 
    //     // {
    //     //     logger_ << Level::INFO << "Error ulock 2\r\n";
    //     // }
    //     // FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_WRPERR);
    //     auto SectorsWRPStatus = FLASH_OB_GetWRP() & FLASH_WRP_SECTORS;

    //     if (SectorsWRPStatus == 0x00)
    //     {
    //         logger_ << Level::INFO << "Unlocking\r\n";
    //     /* If FLASH_WRP_SECTORS are write protected, disable the write protection */

    //     /* Enable the Flash option control register access */
    //     FLASH_OB_Unlock();

    //     /* Disable FLASH_WRP_SECTORS write protection */
    //     FLASH_OB_WRPConfig(FLASH_WRP_SECTORS, DISABLE); 

    //     /* Start the Option Bytes programming process */  
    //     if (FLASH_OB_Launch() == FLASH_COMPLETE)
    //     {
    //         logger_ << Level::INFO << "SUCCESS\r\n";
    //     }
    //     else{
    //         /* User can add here some code to deal with this error */
    //         while (1)
    //         {
    //         }
    //     }
    //     /* Disable the Flash option control register access (recommended to protect 
    //         the option Bytes against possible unwanted operations) */
    //     FLASH_OB_Lock();

    //     /* Get FLASH_WRP_SECTORS write protection status */
    //     SectorsWRPStatus = FLASH_OB_GetWRP() & FLASH_WRP_SECTORS;
    
    //     /* Check if FLASH_WRP_SECTORS write protection is disabled */
    //     if (SectorsWRPStatus == FLASH_WRP_SECTORS)
    //     {
    //         /* OK, turn ON LED1 */
    //      //   STM_EVAL_LEDOn(LED1); 
    //         logger_ << Level::INFO << "unlocked\r\n";
    //     }
    //     else
    //     {
    //         /* KO, turn ON LED3 */
    //         logger_ << Level::INFO << "error\r\n";
    //     //    STM_EVAL_LEDOn(LED3); 
    //     }
    //     }
       
    //     //FLASH_ClearFlag(); 
    //     for (int i = 0; i < msg1.size; i++)
    //     {
    //         u32 startAddress = 0x08004000 + receivedSize + i;
    //         // logger_ << Level::INFO << "D: " << msg1.payload[i] << "\r\n";
    //         int code;
    //         if((code = FLASH_ProgramByte(startAddress, msg1.payload[i])) == FLASH_COMPLETE)
    //         {
    //             //logger_ << Level::ERROR << "Writing flash correct \r\n";
    //         }
    //         else if (code == FLASH_BUSY)
    //         {
    //             logger_ << Level::ERROR << "Writing flash failed FLASH_BUSY \r\n";
    //             return;
    //         }
    //         else if (code == FLASH_ERROR_PROGRAM)
    //         {
    //             logger_ << Level::ERROR << "Writing flash failed FLASH_ERROR_PROGRAM \r\n";
    //             return;
    //         }
    //         else if (code == FLASH_ERROR_WRP)
    //         {
    //             logger_ << Level::ERROR << "Writing flash failed FLASH_ERROR_WRP \r\n";
    //             return;
    //         }
    //         else if (code == FLASH_ERROR_OPERATION)
    //         {
    //             logger_ << Level::ERROR << "Writing flash failed FLASH_ERROR_OPERATION \r\n";
    //             return;
    //         }
    //     }
    //     FLASH_Lock();

    //     for (int i = 0; i < msg1.size; i++)
    //     {
    //         u8 *startAddress = (u8 *)0x08004000;
    //         startAddress += receivedSize;
    //         startAddress += i;
    //         if (*startAddress != msg1.payload[i])
    //         {
    //             logger_ << Level::INFO << "Writing failed: " << *startAddress << " != " << msg1.payload[i] << "\r\n";
    //             return;
    //         }
    //     }

    //     receivedSize += msg1.size;

    // }

    // unsigned long address=0x08004000; 

    // void (*func_ptr)(void) = (void (*)(void))address;
    // func_ptr();
}

void UsartDownloader::waitForProvider()
{
    char downloadCommand[4] = "DWN";
    char buffer[10];
    bool connection = false;
    int index = 0;
    logger_ << Level::INFO << "Waiting for connection \r\n";
    while (!connection) 
    {
        usart::getUsart().send(10, 1);

        logger_ << Level::INFO << "Waiting for message!\r\n";
        auto msg = usart::getUsart().getMessage();
        logger_ << Level::INFO << "Received message with: " << msg.fd << "\r\n";
        if (msg.fd == 10 && msg.payload[0] == 1)
        {
            logger_ << Level::INFO << "Connected to device\r\n";
            connection = true;
        }

        //     logger_ << Level::INFO << "Received byte: " << (int)data << "\n";
        //     if (data == '\n')
        //     {
        //         if (strcmp(buffer, downloadCommand) == 0)
        //         {
        //             logger_ << Level::INFO << "Received " << buffer << " command\n";
        //         }
        //         index = 0;
                
        //     }
        //     else
        //     {
        //         buffer[index++] = data;
        //         buffer[index] = 0;
        //         logger_ << Level::INFO << "Current  " << buffer << " command\n";
                
        //     }
        
    }
     logger_ << Level::INFO << "Exit form func\r\n";
    
}