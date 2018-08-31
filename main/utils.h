#include "esp_bt_defs.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <stdbool.h>

//Transformar endereço no formato 'esp_bd_addr_t' para 'string'
char *bda2str(esp_bd_addr_t bda, char *str, size_t size);

//Transformar valor no formato 'int' para 'string'
char *int2str (int value, char *result, int base);

//Função para esperar 'sec' segundos
void delay(int sec);

//Pegar timestamp atual
char *get_timestamp(void);

//Função apenas para TESTE, a qual seta um timestamp inicial na esp32
void set_date_and_time(void);
