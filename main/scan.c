#include "bluetooth.h"

void update_device_info(esp_bt_gap_cb_param_t *param) {
    char bda_str[18];
    char *address = bda2str(param->disc_res.bda, bda_str, 18);
    if(!exists(address)) { found_device(address,result_callback); }
}

void event_handler(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param) {

    switch (event) {
        
        case ESP_BT_GAP_DISC_RES_EVT: {
            update_device_info(param);
            break;
        }
        case ESP_BT_GAP_DISC_STATE_CHANGED_EVT: {
            if (param->disc_st_chg.state == ESP_BT_GAP_DISCOVERY_STOPPED) {
                ESP_LOGI(GAP_TAG, "Descoberta de dispositivo parada.");

            } else if (param->disc_st_chg.state == ESP_BT_GAP_DISCOVERY_STARTED) {
                ESP_LOGI(GAP_TAG, "Descoberta iniciada.");
            }
            break;
        }
        default: {
            ESP_LOGI(GAP_TAG, "Evento: %d", event);
            break;
        }
    }
    return;
}

void start_scan(int scan_time) {
    clear_scan_result();
    esp_bt_gap_start_discovery(ESP_BT_INQ_MODE_GENERAL_INQUIRY, 10, 0);
    create_scan_result(); 
    delay(scan_time);
    stop_scan(); 
}

void stop_scan() {
    esp_bt_gap_cancel_discovery();
}


