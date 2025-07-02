# 🔧 ESP32 Embedded Firmware Suite

A curated, production-ready suite of 36 hands-on ESP32 firmware projects developed using the **ESP-IDF framework in C**, tailored for embedded engineers, firmware developers, and IoT enthusiasts.

This repository demonstrates real-world embedded applications—from **basic GPIO handling** to **Wi-Fi**, **Bluetooth Low Energy (BLE)**, **FreeRTOS**, **SPI/I2C sensors**, and **cloud connectivity**—using ESP32 SoC for learning, prototyping, and deployment.

---

## 📌 Features

- ✅ Written in **ESP-IDF (C Language)**
- ✅ Clean folder structure for 36 modular projects
- ✅ Real-time tasks via **FreeRTOS**
- ✅ Covers ADC, PWM, UART, BLE, MQTT, HTTP, SPI, I2C, Touch, OTA, and more
- ✅ Ideal for automotive, industrial, and IoT applications

---

## 🛠️ Getting Started

```bash
git clone git@github.com:MAYURDIGAMBARPATIL/esp32_embedded_firmware_suite.git
cd esp32_embedded_firmware_suite
cd 01_gpio   # or any project folder
idf.py set-target esp32
idf.py build flash monitor
