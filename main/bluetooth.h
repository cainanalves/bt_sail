#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_log.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "esp_gap_bt_api.h"
#include "utils.h"

#define GAP_TAG          "GAP"
#define SCANTIME          5

typedef enum {
    APP_GAP_STATE_IDLE = 0,
    APP_GAP_STATE_DEVICE_DISCOVERING,
    APP_GAP_STATE_DEVICE_DISCOVER_COMPLETE,
    APP_GAP_STATE_SERVICE_DISCOVERING,
    APP_GAP_STATE_SERVICE_DISCOVER_COMPLETE,
} app_gap_state_t;

typedef struct {
    bool dev_found;
    uint8_t bdname_len;
    uint8_t eir_len;
    uint8_t rssi;
    uint32_t cod;
    uint8_t eir[ESP_BT_GAP_EIR_DATA_LEN];
    uint8_t bdname[ESP_BT_GAP_MAX_BDNAME_LEN + 1];
    esp_bd_addr_t bda;
    app_gap_state_t state;
} app_gap_cb_t;

typedef struct scan_result {
	char mac[18]; 
	struct scan_result *next;
} scan_result;

static app_gap_cb_t m_dev_info;

void bt_start(char *name);

void paired_devices(void);

void update_device_info(esp_bt_gap_cb_param_t *param);

void event_handler(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param);

void start_scan(int scan_time);

void stop_scan(void);

void start_scan_result();

void found_device(char *addr, void (*scanResultCallback)(char *addr));

int get_size_scan_result();

void clear_scan_result();

void result_callback(char * addr);

bool exists(char *addr);

char *get_JSON();