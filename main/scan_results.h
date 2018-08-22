#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define SCANTIME          5

typedef struct scan_result {
	char mac[18];
	struct scan_result *next;
} scan_result;

void startScanResult();
void printScanResult();
void foundDevice(char *addr, void (*scanResultCallback)(char *addr));
int getSizeScanResult();
void clearScanResult();
bool exists(char *addr);