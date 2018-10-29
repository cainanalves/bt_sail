#include "mqttutils.h"

const char *MQTT_TAG = "MQTT_SAIL";

mqtt_client * gb_mqttClient = NULL;

void connected_cb(void *self, void *params) {
    printf("connected_cb");
    mqtt_client *client = (mqtt_client *)self;
    const char topic_subscribe[] = "ESPsensor"; 
    mqtt_subscribe(client, topic_subscribe, 1);
}

void disconnected_cb(void *self, void *params) {

}

void reconnect_cb(void *self, void *params) {

}

void subscribe_cb(void *self, void *params) {
    ESP_LOGI(MQTT_TAG, "[APP] Subscribe ok");
}

void publish(mqtt_client *client, void *params, char *json, char *topic_publish) {
    mqtt_publish(client, topic_publish, json, strlen(json), 1, 0);
}

void publish_cb(void *self, void *params) {
    xEventGroupSetBits(wifi_event_group, MQTT_PUBLISHED_BIT);
}

void data_cb(void *self, void *params) {
    mqtt_client *client = (mqtt_client *)self;
    mqtt_event_data_t *event_data = (mqtt_event_data_t *)params;
    char *topic = NULL, *data = NULL;

    if(event_data->data_offset == 0) {

        topic = malloc(event_data->topic_length + 1);
        memcpy(topic, event_data->topic, event_data->topic_length);
        topic[event_data->topic_length] = 0;
        ESP_LOGI(MQTT_TAG, "[APP] Publish topic: %s", topic);
    }

    data = malloc(event_data->data_length + 1);
    memcpy(data, event_data->data, event_data->data_length);
    data[event_data->data_length] = 0;
    ESP_LOGI(MQTT_TAG, "[APP] Publish data[%d/%d bytes]",
             event_data->data_length + event_data->data_offset,
             event_data->data_total_length);
    ESP_LOGI(MQTT_TAG, "Publish Data: %s", data);

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
    .client_id = "mqtt_" SENSOR_ID,
    .username = "ESP32_sensorBluetooth" SENSOR_ID,
    .password = SENSOR_KEY,
    .clean_session = 0,
    .keepalive = 120,
    .lwt_topic = "",
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

