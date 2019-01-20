#include "bluetooth.h"
#include "wifi.h"
#include "header_mqtt.h"

EventGroupHandle_t wifi_event_group = NULL;
const int MQTT_PUBLISHED_BIT = BIT1;
//const int MQTT_INITIATE_PUBLISH_BIT = BIT2;
const int CONNECTED_BIT = BIT0;
char *json;

//Notificação de dispositivo encontrado
void result_callback(char *addr) {
	printf("Dispositivo encontrado: %s\n",addr);
}

esp_err_t wifi_event_handler(void *ctx, system_event_t *event) {
    switch(event->event_id) {
        case SYSTEM_EVENT_STA_START:
            esp_wifi_connect();
            break;

        case SYSTEM_EVENT_STA_GOT_IP:
            xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
            gb_mqttClient = mqtt_start(&settings);
            break;

        case SYSTEM_EVENT_STA_DISCONNECTED:
            esp_wifi_connect();
            mqtt_stop();
            gb_mqttClient = NULL;
            xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
            break;

        default:
            break;
    }
    return ESP_OK;
}

void app_main(void) {
	
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

	//Ao ligar a ESP32, é iniciada uma conexão WIFI.
    initialize_wifi();
	//É feita uma sincronização do relógio por meio do protocolo SNTP.
	set_SNTP();
    //set_date_time(); //<-- usar para teste, quando não há conexão com os servidores NTP.
	//O bluetooth é ativado.
    initialize_bt("BT_SAIL"); 
	//São mostrados os dispositivos que já possuem pareamento (sem necessidade especial).
    show_paired_devices(); 
	//É feito um subscribe em um tópico específico (tópico setado dentro do método).
    subscribe_cb(gb_mqttClient, NULL);

    while(true) {
		//Inicia o escaneamento, cuja duração é de SCANTIME segundos
		start_scan(SCANTIME);	
		//Após o escaneamento, o resultado é disponibilizado em formato JSON
        json = get_JSON();		
        if (json == NULL)
            exit(EXIT_FAILURE);
		//É feito um publish do JSON para o tópico 'TOPIC_PUBLISH' 
        publish(gb_mqttClient, NULL, json, TOPIC_PUBLISH);	
		//Limpa a memória
        free(json);	
		//Aguarda-se 10 segundos para o início do próximo escaneamento.
        delay(10); 
    }
	
	
}

