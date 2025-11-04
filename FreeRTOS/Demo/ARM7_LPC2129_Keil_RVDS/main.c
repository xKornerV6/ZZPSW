#include "FreeRTOS.h"
#include "task.h"
#include "led.h"

TaskHandle_t xBlinkHandle;

void Delay(unsigned int uiMiliSec) {
    unsigned int uiLoopCtr, uiDelayLoopCount;
    uiDelayLoopCount = uiMiliSec * 12000;
    for (uiLoopCtr = 0; uiLoopCtr < uiDelayLoopCount; uiLoopCtr++) {
    }
}

void LedBlink(void *pvParameters) {
    while (1) {
        Led_Toggle(0);
        vTaskDelay(pdMS_TO_TICKS(200));
    }
}

void LedCtrl(void *pvParameters) {
    while (1) {
        vTaskSuspend(xBlinkHandle);
        vTaskDelay(pdMS_TO_TICKS(1000));
        vTaskResume(xBlinkHandle);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void) {
    Led_Init();
    xTaskCreate(LedBlink, NULL, 100, NULL, 2, &xBlinkHandle);
    xTaskCreate(LedCtrl, NULL, 100, NULL, 2, NULL);
    vTaskStartScheduler();
    while (1);
}
