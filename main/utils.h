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

int get_timestamp(void);