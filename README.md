# ESP32 Embedded Firmware Suite 🚀

A comprehensive suite of real-world ESP32 embedded firmware projects built using ESP-IDF in C. Includes BLE, Wi-Fi, MQTT, HTTP, SPI, I2C, ADC, FreeRTOS, OTA, and more — ideal for embedded systems and IoT development.

This repository is a **professional collection of 36+ hands-on ESP32 embedded firmware projects**, developed using **ESP-IDF in C language**. It covers essential skills for any embedded firmware engineer, including GPIO, ADC, PWM, UART, Wi-Fi, BLE, FreeRTOS, and peripheral interfacing.

> 🔧 Ideal for: Embedded developers | IoT engineers | ESP32 learners | Job portfolios

---

## 🗂️ Project Index (1–36)

| No. | Project Folder       | Description                               |
|-----|----------------------|-------------------------------------------|
| 01  | `01_gpio`            | Basic GPIO output                         |
| 02  | `02_led_button`      | LED control using push-button             |
| 03  | `03_gpio_interrupt`  | External interrupt on GPIO                |
| 04  | `04_ADC`             | Analog-to-digital conversion              |
| 05  | `05_pwm_adc`         | PWM generation with ADC feedback          |
| 06  | `06_DAC`             | Digital-to-Analog signal output           |
| 07  | `07_UART`            | Serial communication over UART            |
| 08  | `08_wifi`            | Wi-Fi station and access point mode       |
| 09  | `09_ble_adc`         | BLE GATT server with ADC value            |
| 10  | `10_http_server`     | Embedded HTTP server via Wi-Fi            |
| 11  | `11_http_client`     | HTTP client example (GET/POST)            |
| 12  | `12_https_client`    | Secure HTTPS client example               |
| 13  | `13_mqtt_client`     | MQTT protocol with broker communication   |
| 14  | `14_wifi_scan`       | Wi-Fi access point scanning               |
| 15  | `15_sntp`            | NTP time sync using SNTP                  |
| 16  | `16_ota_update`      | OTA firmware update                       |
| 17  | `17_smartconfig`     | Wi-Fi provisioning using SmartConfig      |
| 18  | `18_i2c_lcd`         | I2C LCD 16x2 display driver               |
| 19  | `19_spi_display`     | SPI TFT display driver                    |
| 20  | `20_i2c_oled`        | OLED SSD1306 display via I2C              |
| 21  | `21_rtc_ds1307`      | Real-Time Clock DS1307 via I2C            |
| 22  | `22_sd_card`         | SPI interface with SD card storage        |
| 23  | `23_touch_sensor`    | ESP32 capacitive touch sensor             |
| 24  | `24_adc_dma`         | ADC with DMA for high-speed sampling      |
| 25  | `25_freertos_tasks`  | FreeRTOS task creation & scheduling       |
| 26  | `26_timer`           | Hardware timer example                    |
| 27  | `27_pwm_buzzer`      | Tone generation using PWM (buzzer)        |
| 28  | `28_led_fade`        | LED fading using PWM                      |
| 29  | `29_max31865_spi`    | MAX31865 driver with PT1000 sensor        |
| 30  | `30_ble_beacon`      | BLE beacon (iBeacon) example              |
| 31  | `31_ble_uart_bridge` | BLE ↔ UART transparent data bridge        |
| 32  | `32_esp_now`         | Peer-to-peer ESP-NOW communication        |
| 33  | `33_eeprom_emulation`| EEPROM simulation using flash             |
| 34  | `34_ir_receiver`     | IR signal decoding using TSOP sensor      |
| 35  | `35_hall_sensor`     | Magnetic field sensing (Hall Effect)      |
| 36  | `36_wifi_event`      | Event-based Wi-Fi connection handling     |

> 🧠 Each project includes ESP-IDF code, documentation, and hardware setup (where required).

---

## 🧰 Tech Stack

- **Language**: C
- **MCU**: ESP32-WROOM / DevKit
- **Framework**: ESP-IDF (v4.x / v5.x)
- **RTOS**: FreeRTOS (included in ESP-IDF)
- **Protocols**: BLE, Wi-Fi, MQTT, HTTP/HTTPS, SPI, I2C, UART, OTA, ESP-NOW

---

## 🚀 Getting Started

```bash
git clone https://github.com/MAYURDIGAMBARPATIL/esp32_embedded_firmware_suite.git
cd esp32_embedded_firmware_suite/01_gpio
idf.py set-target esp32
idf.py menuconfig
idf.py build
idf.py flash monitor
