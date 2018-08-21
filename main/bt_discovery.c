
#include "bt_sail.h"

/*char *responses;
int count = 0;

char *createResponsesList(int size){
	char *v = (char *) malloc(size * sizeof(char *));
	return v;
}

bool exists(char *responses, int size, char *addr) {
	for(int rsp = 0;rsp <= size; rsp++){
		if(*responses[rsp] == addr)
			return true;
	}
	return false;
}

void printResponses(char *responses, int size) { 
	for(int rsp = 0;rsp <= size; rsp++){
		printf("%s\n",responses[rsp]);
	}
}
*/
void resultCallback(char *addr) {
	/*if(!exists(responses,count,addr)){
		responses[count] = addr;
		count++;
	}*/
	printf("%s\n",addr);
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

    paired_devices();
    bt_start("ESP32_SAIL");

    while(true){
		startScan();
		startScanResult();
		delay(SCANTIME);
		esp_bt_gap_cancel_discovery();
		clearScanResult();
    }
	
	
}

