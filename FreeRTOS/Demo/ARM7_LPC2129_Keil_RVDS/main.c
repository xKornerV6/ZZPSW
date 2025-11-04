#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"

void LettersTx(void *pvParameters) {
    while(1) {
        Transmiter_SendString("-ABCDEEFGH-\n");
        while (Transmiter_GetStatus() != FREE) {};
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}

int main(void) {
    UART_InitWithInt(300);
    xTaskCreate(LettersTx, NULL, 128, NULL, 1, NULL);
    vTaskStartScheduler();
    while(1);
}
