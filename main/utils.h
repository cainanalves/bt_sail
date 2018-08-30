#include "esp_bt_defs.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>


char *bda2str(esp_bd_addr_t bda, char *str, size_t size);

void delay(int sec);

char *get_timestamp(void);

void set_date_and_time(void);

char *itoaa (int value, char *result, int base);