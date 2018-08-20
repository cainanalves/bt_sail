#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	char *addr;
	struct scan_result *next;
} scan_result;

scan_result *create();
void append(scan_result **sc_rst, char *addr, void (*scanResultCallback)(char *addr));
int getSize(scan_result *sc_rst);
void clearScanResult(scan_result *sc_rst);
void showContent(char * addr);
void getScanResult(scan_result *sc_rst);
bool exists(scan_result *sc_rst, char *addr);