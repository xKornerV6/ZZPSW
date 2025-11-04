#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "semphr.h"

SemaphoreHandle_t xPulseSemaphore;

void PulseTrigger(void *pvParameters) {
    while (1) {
        xSemaphoreGive(xPulseSemaphore);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void Pulse_LED(void *pvParameters) {
    unsigned char ucLedNum = *((unsigned char*)pvParameters);
    while (1) {
        if (xSemaphoreTake(xPulseSemaphore, portMAX_DELAY) == pdTRUE) {
            Led_Toggle(ucLedNum);
            vTaskDelay(pdMS_TO_TICKS(100));
            Led_Toggle(ucLedNum);
        }
    }
}

int main(void) {
    static unsigned char ucLed0 = 0;
    static unsigned char ucLed1 = 1;

    Led_Init();
    xPulseSemaphore = xSemaphoreCreateBinary();
    xTaskCreate(PulseTrigger, NULL, 100, NULL, 2, NULL);
    xTaskCreate(Pulse_LED, NULL, 100, &ucLed0, 2, NULL);
    xTaskCreate(Pulse_LED, NULL, 100, &ucLed1, 2, NULL);
    vTaskStartScheduler();

    while (1);
}
