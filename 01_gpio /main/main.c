#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Define the GPIO pin for the LED
#define LED_GPIO GPIO_NUM_2

void app_main(void)
{
    // Reset the LED GPIO pin to default state
    gpio_reset_pin(LED_GPIO);

    // Set the LED pin as output
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    // Variable to hold LED state (0 or 1)
    uint8_t led_state = 0;

    while (1)
    {
        // Toggle the state
        led_state = !led_state;

        // Apply the state to the GPIO
        gpio_set_level(LED_GPIO, led_state);

        // Wait 500 milliseconds
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}
