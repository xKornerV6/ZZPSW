#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "uart.h"
#include "keyboard.h"
#include "led.h"

SemaphoreHandle_t xUartSemaphore;

void LettersTx(void *pvParameters) {
    while(1) {
        if (xSemaphoreTake(xUartSemaphore, portMAX_DELAY) == pdTRUE) {
            Transmiter_SendString("-ABCDEEFGH-\n");
            while (Transmiter_GetStatus() != FREE) {};
            xSemaphoreGive(xUartSemaphore);
        }
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}

void KeyboardTx(void *pvParameters) {
    enum eKeyboardState ePrevState = RELASED;
    while(1) {
        enum eKeyboardState eCurrentState = eKeyboardRead();
        if (eCurrentState != RELASED && ePrevState == RELASED) {
            if (xSemaphoreTake(xUartSemaphore, portMAX_DELAY) == pdTRUE) {
                Transmiter_SendString("-Keyboard-\n");
                while (Transmiter_GetStatus() != FREE) {};
                xSemaphoreGive(xUartSemaphore);
            }
        }
        ePrevState = eCurrentState;
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

int main(void) {
    Led_Init();
    LedOn(0);  

    UART_InitWithInt(9600);
    KeyboardInit();

    xUartSemaphore = xSemaphoreCreateBinary();
    xSemaphoreGive(xUartSemaphore);

    xTaskCreate(LettersTx, NULL, 128, NULL, 1, NULL);
    xTaskCreate(KeyboardTx, NULL, 128, NULL, 1, NULL);

    vTaskStartScheduler();
    while(1);
}
