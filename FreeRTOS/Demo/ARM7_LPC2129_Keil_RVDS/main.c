#include "FreeRTOS.h"
#include "task.h"
#include "led.h"

typedef struct {
    unsigned char ucLedNumber;
    unsigned char ucFreq;
} LedParams;

void Delay(unsigned int uiMiliSec) {
    unsigned int uiLoopCtr, uiDelayLoopCount;
    uiDelayLoopCount = uiMiliSec * 12000;
    for (uiLoopCtr = 0; uiLoopCtr < uiDelayLoopCount; uiLoopCtr++) {
    }
}

void LedBlink(void *pvParameters) {
    LedParams *pLed = (LedParams *)pvParameters;
    while (1) {
        Led_Toggle(pLed->ucLedNumber);
        vTaskDelay(pdMS_TO_TICKS((1000 / pLed->ucFreq) / 2));
    }
}

void LedCtrl(void *pvParameters) {
    LedParams *pLed = (LedParams *)pvParameters;
    unsigned char ucCounter = 0;
    while (1) {
        pLed->ucFreq++;
        if (pLed->ucFreq > 10) {
            pLed->ucFreq = 1;
        }
        ucCounter++;
        if (ucCounter >= 2) {
            ucCounter = 0;
            pLed->ucLedNumber++;
            if (pLed->ucLedNumber > 1) {
                pLed->ucLedNumber = 0;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main(void) {
    static LedParams xLedParams = {0, 1};
    Led_Init();
    xTaskCreate(LedBlink, NULL, 100, &xLedParams, 2, NULL);
    xTaskCreate(LedCtrl, NULL, 100, &xLedParams, 2, NULL);
    vTaskStartScheduler();
    while (1);
}
