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

#define WIFI_SSID  "..::CAiNaN::.."
#define WIFI_PASS  "98680850cainan"

//POST request
#define WEB_SERVER "10.142.70.238" 
#define WEB_PORT   5000
#define WEB_URL	   "/sensors/scan/1" 
#define MAXLINE    1000
#define MAXSUB     200
#define SA 		   struct sockaddr
//#define LISTENQ    1024

static const int CONNECTED_BIT = BIT0;

//Inicializar WiFi.
void initialize_wifi(void);

//Setar hora e data na ESP32 de acordo com o servidor SNTP.
void set_date_time(void);

//Manipulador de eventos WiFi.
esp_err_t wifi_event_handler(void *ctx, system_event_t *event);

//Enviar dados como requisição POST para: WEB_SERVER; WEB_URL; WEB_PORT. 
void post_request(char *poststr);
