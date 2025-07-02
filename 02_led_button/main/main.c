#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Define GPIOs
#define LED_GPIO    GPIO_NUM_2       // Onboard LED (commonly GPIO2 on ESP32 boards)
#define BUTTON_GPIO GPIO_NUM_12      // Push-button input (active-low)

// Application main entry point
void app_main(void)
{
    // Reset the LED and button GPIOs to default state
    gpio_reset_pin(LED_GPIO);
    gpio_reset_pin(BUTTON_GPIO);

    // Set GPIO directions
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);  // LED as output
    gpio_set_direction(BUTTON_GPIO, GPIO_MODE_INPUT); // Button as input

    // Optional: Configure pull-up resistor if your button needs it
    gpio_set_pull_mode(BUTTON_GPIO, GPIO_PULLUP_ONLY); // Assuming button is active-low

    uint8_t led_state = 0;

    while (1) 
    {
        // Check if button is pressed (logic low)
        if (gpio_get_level(BUTTON_GPIO) == 0) 
        {
            // Toggle LED state
            led_state = !led_state;
            gpio_set_level(LED_GPIO, led_state);

            // Debounce delay to prevent multiple toggles
            vTaskDelay(pdMS_TO_TICKS(300));  // 300ms delay
        }

        // Optional: Small delay to avoid busy looping
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
