#include "FreeRTOS.h"
#include "task.h"
#include "led.h"

void Delay(unsigned int uiMiliSec) {
    unsigned int uiLoopCtr, uiDelayLoopCount;
    uiDelayLoopCount = uiMiliSec * 12000;
    for (uiLoopCtr = 0; uiLoopCtr < uiDelayLoopCount; uiLoopCtr++) {
    }
}

void Led0Blink(void *pvParameters) {
    while (1) {
        Led_Toggle(0);
        Delay(500);
        Led_Toggle(0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void Led1Blink(void *pvParameters) {
    while (1) {
        Led_Toggle(1);
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

int main(void) {
    Led_Init();
    xTaskCreate(Led0Blink, NULL, 100, NULL, 1, NULL);
    xTaskCreate(Led1Blink, NULL, 100, NULL, 3, NULL);
    vTaskStartScheduler();
    while (1);
}
