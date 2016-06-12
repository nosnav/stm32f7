#include "main.h"
#include "WM.h"

uint8_t GUI_Initialized = 0;
void MainTask(void);

int main(void)
{
    System_Init();
    BSP_SDRAM_Init(); /* Initializes the SDRAM device */
    __HAL_RCC_CRC_CLK_ENABLE(); /* Enable the CRC Module */
    GUI_Init();

    GUI_DispStringAt("Starting...", 0, 0);

    GUI_Initialized = 1;

    /* Activate the use of memory device feature */
    WM_SetCreateFlags(WM_CF_MEMDEV);
    MainTask();
  
    /* Infinite loop */
    for(;;);
}

void MainTask(void)
{
    GUI_Clear();
    GUI_SetFont(&GUI_Font20_1);
    GUI_DispStringAt("thanh.duong.vs@gmail.com", 
    (LCD_GetXSize())/2, (LCD_GetYSize()-20)/2);
    while(1);
}
