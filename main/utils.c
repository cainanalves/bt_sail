#include "utils.h"

char *bda2str(esp_bd_addr_t bda, char *str, size_t size) {
	
    if (bda == NULL || str == NULL || size < 18)
    	return NULL;

    uint8_t *p = bda;
    sprintf(str, "%02x:%02x:%02x:%02x:%02x:%02x",
            p[0], p[1], p[2], p[3], p[4], p[5]);
    return str;
}

char *int2str (int value, char *result, int base) {
    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;
}

void delay(int sec) {
	int msec = 1000 * sec;
	clock_t start_time = clock();
	while (clock() < start_time + msec);
}

char *get_timestamp(void) {
    time_t *timestamp;
    time(&timestamp);
    char *str = (char *) malloc(sizeof(char)*20);
    int2str(timestamp, str, 10);
    return str;
}

//Usar apenas para teste
void set_date_time(void) {
    struct timeval tv;
    tv.tv_sec = 123456789;  
    settimeofday(&tv, NULL);
}
