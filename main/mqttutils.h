#ifndef __MQTTUTILS_H__
#define __MQTTUTILS_H__

#include "header_mqtt.h"

void connected_cb(void *self, void *params);

void disconnected_cb(void *self, void *params);

void reconnect_cb(void *self, void *params);

void subscribe_cb(void *self, void *params);

void publish(mqtt_client *client, void *params, char *json, char *topic_publish);    

void publish_cb(void *self, void *params);

void data_cb(void *self, void *params);

extern mqtt_client * gb_mqttClient;

extern mqtt_settings settings;

#endif //__MQTTUTILS_H__
