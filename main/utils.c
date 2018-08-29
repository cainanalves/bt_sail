#include "utils.h"

char *bda2str(esp_bd_addr_t bda, char *str, size_t size) {
	
    if (bda == NULL || str == NULL || size < 18)
    	return NULL;

    uint8_t *p = bda;
    sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x",
            p[0], p[1], p[2], p[3], p[4], p[5]);
    return str;
}

void delay(int sec) {
	int msec = 1000 * sec;
	clock_t start_time = clock();
	while (clock() < start_time + msec);
}

int get_timestamp(void) {
    struct timeval *timestamp;
    gettimeofday(&timestamp, NULL);
    return timestamp;
}

void set_date_and_time(void) {
    struct timeval tv;
    tv.tv_sec = 1535509781; //segundos desde 01 Jan 1970. 
    settimeofday(&tv, NULL);
}