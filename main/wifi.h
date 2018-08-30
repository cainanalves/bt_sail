#include <time.h>
#include <sys/time.h>
#include "esp_attr.h"
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

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

#define WIFI_SSID "UFRN_CERES"
#define WIFI_PASS "UFRN@1306"

#define WEB_SERVER "" //api.thingspeak.com | 10.142.70.238 | 192.168.2.104
#define WEB_PORT 5000
#define WEB_URL "/" //https://api.thingspeak.com/channels/563469/bulk_update.json | /sensors/scan/1

static const int CONNECTED_BIT = BIT0;

void initialize_wifi(void);

void initialize_sntp(void);

void set_date_time(void);

void obtain_time_sntp(void);

esp_err_t wifi_event_handler(void *ctx, system_event_t *event);

ssize_t process_http(int sockfd, char *host, char *page, char *poststr);

void post_request(char *poststr);
