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

#include <netdb.h>
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

#define WIFI_SSID   " " 	//SSID
#define WIFI_PASS   " " 	//password
#define SA      struct sockaddr
#define MAXLINE 1000
#define MAXSUB  200
#define LISTENQ 1024

extern EventGroupHandle_t wifi_event_group;
extern const int CONNECTED_BIT;

//Iniciar conexão WiFi.
void initialize_wifi(void);

//Setar hora e data na ESP32 de acordo com o servidor SNTP.
void set_SNTP(void);

//Manipulador de eventos WiFi.
esp_err_t wifi_event_handler(void *ctx, system_event_t *event);
