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

void Pulse_LED0(void *pvParameters) {
    while (1) {
        if (xSemaphoreTake(xPulseSemaphore, portMAX_DELAY) == pdTRUE) {
            Led_Toggle(0);
            vTaskDelay(pdMS_TO_TICKS(100));
            Led_Toggle(0);
        }
    }
}

int main(void) {
    Led_Init();
    xPulseSemaphore = xSemaphoreCreateBinary();
    xTaskCreate(PulseTrigger, NULL, 100, NULL, 2, NULL);
    xTaskCreate(Pulse_LED0, NULL, 100, NULL, 2, NULL);
    vTaskStartScheduler();
    while (1);
}
