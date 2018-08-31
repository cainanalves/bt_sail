#include "wifi.h"

extern int h_errno;

static EventGroupHandle_t wifi_event_group;

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

esp_err_t wifi_event_handler(void *ctx, system_event_t *event) {
    switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:

        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
        break;
    default:
        break;
    }
    return ESP_OK;
}

void initialize_sntp() {
    ESP_LOGI(TAG, "Inicializando SNTP");
    sntp_setoperatingmode(SNTP_OPMODE_POLL);
    sntp_setservername(0, "pool.ntp.org");
    sntp_init();
}

void obtain_time_sntp() {
    ESP_ERROR_CHECK( nvs_flash_init() );
    xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT,
                        false, true, portMAX_DELAY);
    initialize_sntp();

    time_t now = 0;
    struct tm timeinfo = { 0 };
    int retry = 0;
    const int retry_count = 10;
    while(timeinfo.tm_year < (2016 - 1900) && ++retry < retry_count) {
        ESP_LOGI(TAG, "Aguardando que a hora do sistema seja definida ... (%d/%d)", retry, retry_count);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
        time(&now);
        localtime_r(&now, &timeinfo);
    }

    ESP_ERROR_CHECK( esp_wifi_stop() );
}

void set_date_time(){
    time_t now;
    struct tm timeinfo;
    time(&now);

    localtime_r(&now, &timeinfo);
    if (timeinfo.tm_year < (2016 - 1900)) {
        ESP_LOGI(TAG, "Obtendo o tempo através do Simple Network Time Protocol (SNTP).");
        obtain_time_sntp();
        time(&now);
    }
    char strftime_buf[64];

    setenv("TZ", "EST5EDT,M3.2.0/2,M11.1.0", 1);
    tzset();
    localtime_r(&now, &timeinfo);
    strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
    printf("Data/Hora: %s\n", strftime_buf);
}

ssize_t process_http(int sockfd, char *poststr) {
  char sendline[MAXLINE + 1], recvline[MAXLINE + 1];
  ssize_t n;
  snprintf(sendline, MAXSUB,
      "POST %s HTTP/1.1\r\n"
      "Host: %s\r\n"
      "Content-type: application/json\r\n"
      "Content-length: %d\r\n\r\n"
      "%s", WEB_URL, WEB_SERVER, strlen(poststr), poststr);
  printf("%s\n",sendline);

  write(sockfd, sendline, strlen(sendline));
  while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
    recvline[n] = '\r\n\0';
    printf("%s", recvline);
  }
  return n;
}

void post_request(char *poststr) {
  int sockfd;
  struct sockaddr_in servaddr;

  char **pptr;
  char str[50];
  struct hostent *hptr;

  hptr = gethostbyname(WEB_SERVER);
  if (hptr == NULL) {
    printf("Não foi possível encontrar %s\n",WEB_SERVER);
  }

  printf("hostname: %s\n", hptr->h_name);

  if ((hptr->h_addrtype == AF_INET) && ((pptr = hptr->h_addr_list) != NULL)) {
    printf("address: %s\n",inet_ntop(hptr->h_addrtype, *pptr, str,sizeof(str)));
  }

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(WEB_PORT);
  
  inet_pton(AF_INET, str, &servaddr.sin_addr);
  connect(sockfd, (SA *) & servaddr, sizeof(servaddr));
  process_http(sockfd, poststr);
  close(sockfd);
}