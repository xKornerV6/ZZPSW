#include "FreeRTOS.h"
#include "task.h"
#include "led.h"

void Led0Blink(void *pvParameters) {
    while (1) {
        Led_Toggle(0);
        vTaskDelay(pdMS_TO_TICKS(1000));   // 0.5 Hz
    }
}

void Led1Blink(void *pvParameters) {
    while (1) {
        Led_Toggle(1);
        vTaskDelay(pdMS_TO_TICKS(50));     // 10 Hz
    }
}

int main(void) {
    Led_Init();
    xTaskCreate(Led0Blink, NULL, 100, NULL, 2, NULL);
    xTaskCreate(Led1Blink, NULL, 100, NULL, 2, NULL);
    vTaskStartScheduler();
    while (1);
}
