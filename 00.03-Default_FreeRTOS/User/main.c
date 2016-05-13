#include "main.h"

osThreadId LED_ThreadId;
static void LED_Thread(void const *argument);

int main(void)
{
    System_Init();
    LED_Init();
    
    /* Thread 1 definition */
    osThreadDef(LED1, LED_Thread, osPriorityNormal, 0, configMINIMAL_STACK_SIZE);

    /* Start thread 1 */
    LED_ThreadId = osThreadCreate(osThread(LED1), NULL);

    /* Start scheduler */
    osKernelStart();

    /* We should never get here as control is now taken by the scheduler */
    for(;;);
}

static void LED_Thread(void const *argument)
{
    (void) argument;
    //uint32_t PreviousWakeTime = osKernelSysTick();

    for(;;)
    {
        //osDelayUntil (&PreviousWakeTime, 500);
        LED_Toggle();
        osDelay(500);
    }
}
