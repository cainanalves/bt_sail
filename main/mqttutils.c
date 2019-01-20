#include "mqttutils.h"
#include "utils.h"

const char *MQTT_TAG = "MQTT_SAIL";

mqtt_client * gb_mqttClient = NULL;

void connected_cb(void *self, void *params) {
    mqtt_client *client = (mqtt_client *)self;
    const char topic_subscribe[] = TOPIC_SUBSCRIBE; 
    mqtt_subscribe(client, topic_subscribe, 1);
}

void disconnected_cb(void *self, void *params) {

}

void reconnect_cb(void *self, void *params) {

}

void subscribe_cb(void *self, void *params) {
    ESP_LOGI(MQTT_TAG, "[APP] Subscribe topic [%s] ok", TOPIC_SUBSCRIBE);
}

void publish(mqtt_client *client, void *params, char *json, char *topic_publish) {
    mqtt_publish(client, topic_publish, json, strlen(json), 1, 0);
}

void publish_cb(void *self, void *params) {
    xEventGroupSetBits(wifi_event_group, MQTT_PUBLISHED_BIT);
}

void interprete_data(mqtt_client *client, int dataInt){
    
    switch (dataInt) {
        
        case 1: {
            publish(client,NULL,"[ESP] restart",TOPIC_SUBSCRIBE);
            delay(1);
            esp_restart();
            break;
        }
        
        default: {
            
            break;
        }
    }
}

void data_cb(void *self, void *params) {
    mqtt_client *client = (mqtt_client *) self;
    mqtt_event_data_t *event_data = (mqtt_event_data_t *)params;
    char *topic = NULL, *data = NULL;

    if(event_data->data_offset == 0) {
        topic = malloc(event_data->topic_length + 1);
        memcpy(topic, event_data->topic, event_data->topic_length);
        topic[event_data->topic_length] = 0;
        ESP_LOGI(MQTT_TAG, "[MQTT] Publish topic: %s", topic);
    }

    data = malloc(event_data->data_length + 1);
    memcpy(data, event_data->data, event_data->data_length);
    data[event_data->data_length] = 0;
    ESP_LOGI(MQTT_TAG, "[MQTT] Publish data[%d/%d bytes]",
             event_data->data_length + event_data->data_offset,
             event_data->data_total_length);
    ESP_LOGI(MQTT_TAG, "Publish Data: %s", data);

    int dataInt = atoi(data);
    interprete_data(client,dataInt);

    free(topic);
    free(data);
}

mqtt_settings settings = {
    .host = WEB_SERVER,
/*
#if defined(CONFIG_MQTT_SECURITY_ON)
    .port = 8883, // encrypted
#else
    .port = 1883, // unencrypted
#endif
*/
    .port = WEB_PORT,
    .client_id = "BT_SAIL_" SENSOR_ID,
    .username = "bt_sail_" SENSOR_ID,
    .password = SENSOR_KEY,
    .clean_session = 0,
    .keepalive = 120,
    .lwt_topic = TOPIC_PUBLISH,
    .lwt_msg = "",
    .lwt_qos = 0,
    .lwt_retain = 0,
    .connected_cb = connected_cb,
    .disconnected_cb = disconnected_cb,
    //.reconnect_cb = reconnect_cb,
    .subscribe_cb = subscribe_cb,
    .publish_cb = publish_cb,
    .data_cb = data_cb
};

