#include <stdio.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "esp_bt.h"
#include "esp_gap_ble_api.h"
#include "esp_gatts_api.h"
#include "esp_bt_defs.h"
#include "esp_bt_main.h"
#include "esp_gatt_common_api.h"
#include "driver/adc.h"

#define TAG "BLE_ADC"
#define GATTS_SERVICE_UUID_TEST    0x00FF
#define GATTS_CHAR_UUID_ADC        0xFF01
#define GATTS_NUM_HANDLE_TEST      4
#define DEVICE_NAME                "ESP32_ADC_BLE"
#define PROFILE_NUM                1
#define PROFILE_APP_IDX            0

static uint16_t gatts_if_handle = 0;
static uint16_t conn_id = 0;
static esp_gatt_if_t gatts_if_global = 0;
static bool is_connected = false;

static uint8_t adc_value_notify[2]; // 2 bytes for uint16_t ADC

static uint16_t gatt_db_handle_table[GATTS_NUM_HANDLE_TEST];

/// Attributes State Machine
enum {
    IDX_SERVICE,
    IDX_CHAR_ADC,
    IDX_CHAR_VAL_ADC,
};

/// Full GATT database
static const esp_gatts_attr_db_t gatt_db[GATTS_NUM_HANDLE_TEST] =
{
    // Service
    [IDX_SERVICE] = {
        {ESP_GATT_AUTO_RSP},
        {
            ESP_UUID_LEN_16, (uint8_t*)&primary_service_uuid,
            ESP_GATT_PERM_READ,
            sizeof(uint16_t), sizeof(GATTS_SERVICE_UUID_TEST),
            (uint8_t*)&GATTS_SERVICE_UUID_TEST
        }
    },

    // Characteristic Declaration
    [IDX_CHAR_ADC] = {
        {ESP_GATT_AUTO_RSP},
        {
            ESP_UUID_LEN_16, (uint8_t*)&character_declaration_uuid,
            ESP_GATT_PERM_READ,
            sizeof(uint8_t), sizeof(uint8_t),
            (uint8_t*)&char_prop_notify
        }
    },

    // Characteristic Value (ADC)
    [IDX_CHAR_VAL_ADC] = {
        {ESP_GATT_RSP_BY_APP},
        {
            ESP_UUID_LEN_16, (uint8_t*)&GATTS_CHAR_UUID_ADC,
            ESP_GATT_PERM_READ,
            2, 0, NULL
        }
    }
};

/// GATT server callback
static void gatts_profile_event_handler(
    esp_gatts_cb_event_t event, esp_gatt_if_t gatts_if,
    esp_ble_gatts_cb_param_t *param)
{
    switch (event) {
        case ESP_GATTS_CONNECT_EVT:
            ESP_LOGI(TAG, "Client connected");
            is_connected = true;
            conn_id = param->connect.conn_id;
            gatts_if_handle = param->connect.gatt_if;
            break;

        case ESP_GATTS_DISCONNECT_EVT:
            ESP_LOGI(TAG, "Client disconnected");
            is_connected = false;
            esp_ble_gap_start_advertising(&adv_params);
            break;

        case ESP_GATTS_READ_EVT: {
            uint16_t adc = adc1_get_raw(ADC1_CHANNEL_0);
            adc_value_notify[0] = adc & 0xFF;
            adc_value_notify[1] = (adc >> 8) & 0xFF;
            esp_ble_gatts_send_response(
                gatts_if, param->read.conn_id, param->read.trans_id,
                ESP_GATT_OK, NULL);
            break;
        }

        case ESP_GATTS_CREATE_EVT:
            gatt_db_handle_table[IDX_SERVICE] = param->create.service_handle;
            esp_ble_gatts_start_service(param->create.service_handle);
            esp_ble_gatts_add_char(param->create.service_handle,
                &GATTS_CHAR_UUID_ADC,
                ESP_GATT_PERM_READ,
                ESP_GATT_CHAR_PROP_BIT_READ | ESP_GATT_CHAR_PROP_BIT_NOTIFY,
                NULL, NULL);
            break;

        case ESP_GATTS_ADD_CHAR_EVT:
            gatt_db_handle_table[IDX_CHAR_VAL_ADC] = param->add_char.attr_handle;
            break;

        default:
            break;
    }
}

/// BLE Initialization
static void ble_init()
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    esp_bt_controller_init(&bt_cfg);
    esp_bt_controller_enable(ESP_BT_MODE_BLE);
    esp_bluedroid_init();
    esp_bluedroid_enable();

    esp_ble_gatts_register_callback(gatts_profile_event_handler);
    esp_ble_gatts_app_register(PROFILE_APP_IDX);
    esp_ble_gap_set_device_name(DEVICE_NAME);
}

/// BLE Notification Task
void adc_notify_task(void *arg)
{
    while (1) {
        if (is_connected) {
            uint16_t adc = adc1_get_raw(ADC1_CHANNEL_0);
            adc_value_notify[0] = adc & 0xFF;
            adc_value_notify[1] = (adc >> 8) & 0xFF;

            esp_ble_gatts_send_indicate(
                gatts_if_handle, conn_id,
                gatt_db_handle_table[IDX_CHAR_VAL_ADC],
                sizeof(adc_value_notify),
                adc_value_notify,
                false);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    // Init ADC
    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_11);

    // Init BLE
    ble_init();

    // Start task to send ADC data
    xTaskCreate(adc_notify_task, "adc_notify_task", 2048, NULL, 5, NULL);
}
