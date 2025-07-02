#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"
#include "driver/ledc.h"

#define PWM_GPIO       GPIO_NUM_2               // PWM output
#define ADC_GPIO       ADC1_CHANNEL_7           // GPIO 35

void app_main(void)
{
    // 1. Configure PWM on GPIO 2 using LEDC
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_LOW_SPEED_MODE,
        .duty_resolution  = LEDC_TIMER_8_BIT,
        .timer_num        = LEDC_TIMER_0,
        .freq_hz          = 5000,
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ledc_timer_config(&ledc_timer);

    ledc_channel_config_t ledc_channel = {
        .channel    = LEDC_CHANNEL_0,
        .duty       = 0,
        .gpio_num   = PWM_GPIO,
        .speed_mode = LEDC_LOW_SPEED_MODE,
        .hpoint     = 0,
        .timer_sel  = LEDC_TIMER_0
    };
    ledc_channel_config(&ledc_channel);

    // 2. Configure ADC1 channel 7 (GPIO 35)
    adc1_config_width(ADC_WIDTH_BIT_12);                         // 12-bit ADC
    adc1_config_channel_atten(ADC_GPIO, ADC_ATTEN_DB_11);        // For 3.3V range

    // 3. Loop: Increase PWM and read voltage from ADC
    while (1)
    {
        for (int duty = 0; duty <= 255; duty += 25)
        {
            ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, duty);
            ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);

            vTaskDelay(pdMS_TO_TICKS(100));  // Let PWM settle

            int adc_value = adc1_get_raw(ADC_GPIO);
            float voltage = (adc_value * 3.3) / 4095.0;
            printf("Duty: %3d, ADC: %4d, Voltage: %.2f V\n", duty, adc_value, voltage);

        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
