#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/gpio.h"


#define UART_PORT       UART_NUM_2
#define TX_PIN          GPIO_NUM_17
#define RX_PIN          GPIO_NUM_16
#define BUF_SIZE        1024

char *tx_data = "Hi I am from ESP32\n";     // Transmit string
uint8_t rx_data[BUF_SIZE];                  // Receive buffer

void app_main(void)
{
    // Configure UART parameters
    uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };

    // Apply UART configuration
    uart_param_config(UART_PORT, &uart_config);

    // Set UART Tx/Rx pins (no RTS/CTS flow control)
    uart_set_pin(UART_PORT, TX_PIN, RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);

    // Install UART driver with receive buffer, no event queue
    uart_driver_install(UART_PORT, BUF_SIZE, 0, 0, NULL, 0);

    while (1)
    {
        // Transmit string over UART
        uart_write_bytes(UART_PORT, tx_data, strlen(tx_data));

        // Try reading up to 128 bytes from UART with 5ms timeout
        int len = uart_read_bytes(UART_PORT, rx_data, 128, pdMS_TO_TICKS(5));

        if (len > 0)
        {
            rx_data[len] = '\0';  // Null-terminate received data
            printf("Received (%d bytes): %s\n", len, rx_data);
        }

        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
