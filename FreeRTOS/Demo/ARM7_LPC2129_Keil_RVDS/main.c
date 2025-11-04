#include "FreeRTOS.h"
#include "task.h"
#include "led.h"

void Delay(unsigned int uiMiliSec) {
    unsigned int uiLoopCtr, uiDelayLoopCount;
    uiDelayLoopCount = uiMiliSec * 12000;
    for (uiLoopCtr = 0; uiLoopCtr < uiDelayLoopCount; uiLoopCtr++) {
    }
}

void LedBlink(void *pvParameters) {
    unsigned char *pucFreq = (unsigned char *)pvParameters;
    while (1) {
        Led_Toggle(0);
        vTaskDelay(pdMS_TO_TICKS((1000 / *pucFreq) / 2));
    }
}

void LedCtrl(void *pvParameters) {
    unsigned char *pucFreq = (unsigned char *)pvParameters;
    while (1) {
        (*pucFreq)++;
        if (*pucFreq > 10) {
            *pucFreq = 1;
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void) {
    static unsigned char ucBlinkingFreq = 1;
    Led_Init();
    xTaskCreate(LedBlink, NULL, 100, &ucBlinkingFreq, 2, NULL);
    xTaskCreate(LedCtrl, NULL, 100, &ucBlinkingFreq, 2, NULL);
    vTaskStartScheduler();
    while (1);
}
