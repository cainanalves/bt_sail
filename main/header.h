#ifndef __HEADER_H__
#define __HEADER_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "esp_wifi.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "esp_event_loop.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"

#include "lwip/sockets.h"
#include "lwip/dns.h"
#include "lwip/netdb.h"

#include "esp_log.h"
#include "mqtt.h"

#include "driver/adc.h"
#include "esp_adc_cal.h"

#include "mqttutils.h"
#include "wifi.h"

//#define SOFTAP_SSID                 "cainan"	//"ESP32AP"
//#define SOFTAP_PASSWORD             "j5xhYdSjls"	//"abcdefpassword"

#define WEB_SERVER                  "10.142.71.186"	//"192.168.2.104"
#define WEB_PORT                    1883            // should be an integer and not a string

#define SENSOR_ID                   "20a75dde953a" //"c6f900db58e9"
#define SENSOR_KEY                  "ff121d68cd4b52eaed5b9455453c81ba"	//"2d9a97f168db68ae6f94b1b547581c1f"

#define ADC_ACCURACY                4                                  //in percentage

extern const int MQTT_PUBLISHED_BIT;
extern const int MQTT_INITIATE_PUBLISH_BIT;

#endif //__HEADER_H__
