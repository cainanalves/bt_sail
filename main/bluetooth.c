#include "bluetooth.h"

static app_gap_cb_t m_dev_info;

void initialize_bt(char *name) {

    esp_bt_dev_set_device_name(name);

    /* definir o modo detectável e conectável, aguarde para ser conectado */
    esp_bt_gap_set_scan_mode(ESP_BT_SCAN_MODE_CONNECTABLE_DISCOVERABLE);

    /* registrar função de retorno de chamada GAP */
    esp_bt_gap_register_callback(event_handler);

    /* inicializar informações e status do dispositivo */
    app_gap_cb_t *p_dev = &m_dev_info;
    memset(p_dev, 0, sizeof(app_gap_cb_t));

    /* descobrir dispositivos Bluetooth próximos */
    p_dev->state = APP_GAP_STATE_DEVICE_DISCOVERING;
    
}

void get_paired_devices(void) {
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