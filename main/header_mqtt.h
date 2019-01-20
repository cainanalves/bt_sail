#ifndef __HEADER_H__
#define __HEADER_H__

#include "wifi.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

#include "freertos/semphr.h"
#include "freertos/queue.h"

#include "mqtt.h"

#include "esp_adc_cal.h"

#include "mqttutils.h"


#define WEB_SERVER                  " " 	//ex: 192.168.0.2
#define WEB_PORT                    1883 	//<- Porta padrão
#define TOPIC_PUBLISH               "ESP_BT_PUB"
#define TOPIC_SUBSCRIBE             "ESP_BT_SUB"


#define SENSOR_ID                   "20a75dde953a" 
#define SENSOR_KEY                  "ff121d68cd4b52eaed5b9455453c81ba"	

extern const int MQTT_PUBLISHED_BIT;
extern const int MQTT_INITIATE_PUBLISH_BIT;

#endif //__HEADER_H__
