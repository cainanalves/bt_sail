
#include "bt_sail.h"

void resultCallback(char *addr) {
	printf("Dispositivo encontrado: %s\n",addr);
}

void app_main() {
    
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    if ((ret = esp_bt_controller_init(&bt_cfg)) != ESP_OK) {
        ESP_LOGE(GAP_TAG, "%s falha ao inicializar o controlador: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bt_controller_enable(ESP_BT_MODE_BTDM)) != ESP_OK) {
        ESP_LOGE(GAP_TAG, "%s falha ao ativar o controlador: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bluedroid_init()) != ESP_OK) {
        ESP_LOGE(GAP_TAG, "%s falha ao inicializar o bluedroid: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bluedroid_enable()) != ESP_OK) {
        ESP_LOGE(GAP_TAG, "%s falha ao ativar o bluedroid: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    pairedDevices();
    btStart("ESP32_SAIL");

    while(true){
		startScan(SCANTIME);
		delay(10); //Em segundos
    }
	
	
}

