#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

// Define the GPIO pin for external interrupt (e.g., button)
#define INTERRUPT_GPIO GPIO_NUM_5

// Global variables
static volatile uint16_t interrupt_count = 0;
static volatile bool button_pressed = false;

// ISR Handler — runs in interrupt context (must be short and efficient)
static void IRAM_ATTR gpio_isr_handler(void *arg)
{
    interrupt_count++;
    button_pressed = true;
    // Do NOT call gpio_isr_handler_add or gpio_intr_enable inside ISR
}

void app_main(void)
{
    // Reset pin to default state
    gpio_reset_pin(INTERRUPT_GPIO);

    // Set GPIO as input
    gpio_set_direction(INTERRUPT_GPIO, GPIO_MODE_INPUT);

    // Enable internal pull-up (for active-low button)
    gpio_set_pull_mode(INTERRUPT_GPIO, GPIO_PULLUP_ONLY);

    // Configure interrupt on rising edge (change to GPIO_INTR_NEGEDGE for falling edge)
    gpio_set_intr_type(INTERRUPT_GPIO, GPIO_INTR_POSEDGE);

    // Install GPIO ISR service (0 = default interrupt allocation flags)
    gpio_install_isr_service(0);

    // Attach the ISR handler to the pin
    gpio_isr_handler_add(INTERRUPT_GPIO, gpio_isr_handler, NULL);

    // Enable interrupt (optional — already enabled when type is set)
    gpio_intr_enable(INTERRUPT_GPIO);

    // Main task loop
    while (1)
    {
        if (button_pressed)
        {
            printf("Interrupt Count: %d\n", interrupt_count);
            button_pressed = false;
        }

        // Delay to avoid busy-waiting (100ms)
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
