#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "cJSON.h"

#define SCANTIME          5

typedef struct scan_result {
	char mac[18]; 
	//timestamp
	struct scan_result *next;
} scan_result;

void start_scan_result();

void print_scan_result();

void found_device(char *addr, void (*scanResultCallback)(char *addr));

int get_size_scan_result();

void clear_scan_result();

bool exists(char *addr);

char *get_JSON();