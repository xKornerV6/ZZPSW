#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"
#include "keyboard.h"

void LettersTx(void *pvParameters) {
    while(1) {
        Transmiter_SendString("-ABCDEEFGH-\n");
        while (Transmiter_GetStatus() != FREE) {};
        vTaskDelay(pdMS_TO_TICKS(300));
    }
}

void KeyboardTx(void *pvParameters) {
    enum eKeyboardState ePrevState = RELASED;
    while(1) {
        enum eKeyboardState eCurrentState = eKeyboardRead();
        if (eCurrentState != RELASED && ePrevState == RELASED) {
            Transmiter_SendString("-Keyboard-\n");
            while (Transmiter_GetStatus() != FREE) {};
        }
        ePrevState = eCurrentState;
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

int main(void) {
    UART_InitWithInt(9600);
    KeyboardInit();
    xTaskCreate(LettersTx, NULL, 128, NULL, 1, NULL);
    xTaskCreate(KeyboardTx, NULL, 128, NULL, 1, NULL);
    vTaskStartScheduler();
    while(1);
}
