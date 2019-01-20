#include "wifi.h"

static const char *TAG = "WiFi_SAIL";

void initialize_wifi() {
    tcpip_adapter_init();
    wifi_event_group = xEventGroupCreate();
    ESP_ERROR_CHECK( esp_event_loop_init(wifi_event_handler, NULL) );
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK( esp_wifi_init(&cfg) );
    ESP_ERROR_CHECK( esp_wifi_set_storage(WIFI_STORAGE_RAM) );
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
        },
    };

    ESP_LOGI(TAG, "Configurando o WiFi com SSID %s ...", wifi_config.sta.ssid);
    ESP_ERROR_CHECK( esp_wifi_set_mode(WIFI_MODE_STA) );
    ESP_ERROR_CHECK( esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );
    ESP_ERROR_CHECK( esp_wifi_start() );
}

void initialize_sntp() {
    ESP_LOGI(TAG, "Inicializando SNTP");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);

		//pool.ntp.org <- servidor padrão
		//ntp.ufrn.br  <- servidor da UFRN

    sntp_setservername(0, "ntp.ufrn.br"); 
    sntp_init();
}

void obtain_time_sntp() {
    ESP_ERROR_CHECK( nvs_flash_init() );
    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);
    initialize_sntp();

    time_t now = 0;
    struct tm timeinfo = { 0 };
    int retry = 0;
    const int retry_count = 10;
    while(timeinfo.tm_year < (2019 - 1900) && ++retry < retry_count) {
        ESP_LOGI(TAG, "Aguardando que a hora do sistema seja definida ... (%d/%d)", retry, retry_count);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        time(&now);
        localtime_r(&now, &timeinfo);
    }
}

void set_SNTP(){
    time_t now;
    struct tm timeinfo;
    time(&now);

    localtime_r(&now, &timeinfo);
    if (timeinfo.tm_year < (2019 - 1900)) {
        ESP_LOGI(TAG, "Sincronização do relógio através do Simple Network Time Protocol (SNTP).");
        obtain_time_sntp();
        time(&now);
    }
    char strftime_buf[64];

    setenv("TZ", "BRT3BRST,M10.3.0,M2.3.0", 1); // <-- TimeZone 
    tzset();
    localtime_r(&now, &timeinfo);
    strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
    printf("Data/Hora: %s\n", strftime_buf);
}
