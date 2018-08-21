#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
	char *addr;
	struct scan_result *next;
} scan_result;

#define SCANTIME          10

void startScanResult();
scan_result *getScanResult();
void append(char *addr, void (*scanResultCallback)(char *addr));
int getSize(scan_result *sc_rst);
void clearScanResult();
bool exists(char *addr);