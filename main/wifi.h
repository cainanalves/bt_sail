#include <time.h>
#include <sys/time.h>
#include "esp_attr.h"
//#include "esp_sleep.h"
#include "settings_wifi.h"
#include "apps/sntp/sntp.h"

static const char *TAG = "WiFi_SAIL";

void initialize_wifi(void);

void initialize_sntp(void);

void set_date_time(void);

void obtain_time_sntp(void);

esp_err_t wifi_event_handler(void *ctx, system_event_t *event);

void send_data(char *data);