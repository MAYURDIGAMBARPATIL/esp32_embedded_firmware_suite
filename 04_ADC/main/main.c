#include <stdio.h>
#include "driver/adc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Variable to hold ADC value
int adc_value = 0;

void app_main(void)
{
    // Configure ADC width to 12-bit (0 - 4095 range)
    adc1_config_width(ADC_WIDTH_BIT_12);

    // Configure ADC channel attenuation
    // ADC1_CHANNEL_7 = GPIO35
    adc1_config_channel_atten(ADC1_CHANNEL_7, ADC_ATTEN_DB_11);

    // Infinite loop to read ADC values
    while (true)
    {
        // Read raw ADC value
        adc_value = adc1_get_raw(ADC1_CHANNEL_7);

        // Print ADC value
        printf("ADC Value is %d\n", adc_value);

        // Delay 1 second
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
