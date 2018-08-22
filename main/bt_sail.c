#include "bt_sail.h"

void updateDeviceInfo(esp_bt_gap_cb_param_t *param) {
    char bda_str[18];
    char *address = bda2str(param->disc_res.bda, bda_str, 18);
    if(!exists(address))
      foundDevice(address,resultCallback);
}

void eventHandler(esp_bt_gap_cb_event_t event, esp_bt_gap_cb_param_t *param) {

    switch (event) {
	    case ESP_BT_GAP_DISC_RES_EVT: {
	        updateDeviceInfo(param);
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

void btStart(char *name) {

    esp_bt_dev_set_device_name(name);

    /* definir o modo detectável e conectável, aguarde para ser conectado */
    esp_bt_gap_set_scan_mode(ESP_BT_SCAN_MODE_CONNECTABLE_DISCOVERABLE);

    /* registrar função de retorno de chamada GAP */
    esp_bt_gap_register_callback(eventHandler);

    /* inicializar informações e status do dispositivo */
    app_gap_cb_t *p_dev = &m_dev_info;
    memset(p_dev, 0, sizeof(app_gap_cb_t));

    /* descobrir dispositivos Bluetooth próximos */
    p_dev->state = APP_GAP_STATE_DEVICE_DISCOVERING;
    
}

void pairedDevices() {
  int dev_num = esp_bt_gap_get_bond_device_num();
  esp_bd_addr_t *dev_list = (esp_bd_addr_t *)malloc(sizeof(esp_bd_addr_t) * dev_num);
  esp_bt_gap_get_bond_device_list(&dev_num, dev_list);
  printf( "-------------------------------------|\nEmparelhados pelo menos uma vez: %d   |\n",dev_num);
  for (int i = 0; i < dev_num; i++) {
      printf( "%02x:%02x:%02x:%02x:%02x:%02x                    |\n", ESP_BD_ADDR_HEX(dev_list[i]));
  }
  printf( "-------------------------------------|\n");
  free(dev_list);
}

void startScan(int scan_time) {
  clearScanResult();
	esp_bt_gap_start_discovery(ESP_BT_INQ_MODE_GENERAL_INQUIRY, 10, 0);
	startScanResult(); 
  delay(scan_time);
  stopScan(); 
}

void stopScan() {
  esp_bt_gap_cancel_discovery();
}


