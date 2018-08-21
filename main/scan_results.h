#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

typedef struct scan_result {
	char mac[18];
	struct scan_result *next;
} scan_result;

#define SCANTIME          15

scan_result *startScanResult(scan_result *sc_rst);
void printScanResult(scan_result *sc_rst);
void append(scan_result **sc_rst, char *addr, void (*scanResultCallback)(char *addr));
int getSizeScanResult(scan_result *sc_rst);
void clearScanResult(scan_result *sc_rst);
bool exists(scan_result *sc_rst, char *addr);