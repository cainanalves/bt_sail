#include <time.h>
#include <sys/time.h>
#include "esp_attr.h"
//#include "esp_sleep.h"
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
#include "apps/sntp/sntp.h"

#define WIFI_SSID "..::CAiNaN::.."
#define WIFI_PASS "98680850cainan"

#define WEB_SERVER "api.thingspeak.com"
#define WEB_PORT 80
#define WEB_URL "https://api.thingspeak.com/channels/563469/bulk_update.json"

static EventGroupHandle_t wifi_event_group;

static const int CONNECTED_BIT = BIT0;

static const char *TAG = "WiFi_SAIL";

void initialize_wifi(void);

void initialize_sntp(void);

void set_date_time(void);

void obtain_time_sntp(void);

esp_err_t wifi_event_handler(void *ctx, system_event_t *event);

void send_data(char *data);