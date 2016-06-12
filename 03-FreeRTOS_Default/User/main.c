#include "main.h"

static void TaskLED(void *pvParameters);

int main(void)
{
    System_Init();
    LED_Init(LED1);
    xTaskCreate(TaskLED, "TaskLED", configMINIMAL_STACK_SIZE, NULL, 0, NULL);
    vTaskStartScheduler();
}

static void TaskLED(void *pvParameters)
{
    for(;;)
    {
        LED_Toggle(LED1);
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}
