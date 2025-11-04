#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "uart.h"
#include "keyboard.h"

SemaphoreHandle_t xSemaphore;

void Rtos_Transmiter_SendString(char *pcString) {
    xSemaphoreTake(xSemaphore, portMAX_DELAY);
    Transmiter_SendString(pcString);
    while (Transmiter_GetStatus() != FREE) {}
    xSemaphoreGive(xSemaphore);
}

void LettersTx(void *pvParameters) {
    while (1) {
        Rtos_Transmiter_SendString("-ABCDEEFGH-\n");
        vTaskDelay(300);
    }
}

void KeyboardTx(void *pvParameters) {
    enum eKeyboardState eKey;
    while (1) {
        eKey = eKeyboardRead();
        if (eKey != RELASED) {
            Rtos_Transmiter_SendString("-Keyboard-\n");
        }
        vTaskDelay(100);
    }
}

int main(void) {
    UART_InitWithInt(9600);
    KeyboardInit();
    xSemaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(xSemaphore);
    xTaskCreate(LettersTx, NULL, 128, NULL, 1, NULL);
    xTaskCreate(KeyboardTx, NULL, 128, NULL, 1, NULL);
    vTaskStartScheduler();
    while (1);
}
