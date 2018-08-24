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

#define WIFI_SSID "..::CAiNaN::.."
#define WIFI_PASS "98680850cainan"

#define WEB_SERVER "api.thingspeak.com"
#define WEB_PORT 80
#define WEB_URL "https://api.thingspeak.com/channels/563469/bulk_update.json"

static EventGroupHandle_t wifi_event_group;

static const int CONNECTED_BIT = BIT0;


    