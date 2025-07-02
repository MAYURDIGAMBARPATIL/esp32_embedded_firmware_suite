#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/dac.h"

// DAC1 is on GPIO25, DAC_CHANNEL_1
void app_main(void)
{
    // Enable DAC output on channel 1 (GPIO25)
    dac_output_enable(DAC_CHANNEL_1);

    while (1)
    {
        // Rising ramp: 0 → 255
        for (int i = 0; i <= 255; i++)
        {
            dac_output_voltage(DAC_CHANNEL_1, i);
            printf("DAC Output: %d\n", i);
            vTaskDelay(pdMS_TO_TICKS(20)); // 20ms delay
        }

        // Falling ramp: 255 → 0
        for (int i = 255; i >= 0; i--)
        {
            dac_output_voltage(DAC_CHANNEL_1, i);
            printf("DAC Output: %d\n", i);
            vTaskDelay(pdMS_TO_TICKS(20)); // 20ms delay
        }
    }
}
