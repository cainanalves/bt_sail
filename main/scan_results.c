#include "scan_results.h"

scan_result *sc_rst;

void startScanResult() {
	sc_rst = NULL;
}

void printScanResult() {
	scan_result *aux = sc_rst;
	while(aux != NULL){
		printf("%s\n",aux->mac);
		aux = aux->next;	
	}
}

scan_result *newAddress(char *addr) {
    scan_result *newaddress = (scan_result *) malloc(sizeof(scan_result));
    strcpy(newaddress->mac,addr);
    newaddress->next = NULL;
    return newaddress;
}

void foundDevice(char *addr, void (* scanResultCallback)(char *addr)) {
	scan_result *newaddress = newAddress(addr);
    if (sc_rst == NULL){
        sc_rst = newaddress;
    }else{
		newaddress->next = sc_rst->next;
    	sc_rst->next = newaddress;
    }
    scanResultCallback(newaddress->mac);
}

int getSizeScanResult() {
	scan_result *sc = sc_rst;
	int count = 0;
	while(sc != NULL){
		count++;
		sc = sc->next;
	}
	return count;
}

void clearScanResult() {
	free(sc_rst);
}

bool exists(char *addr) {
	scan_result *aux = sc_rst;
	while(aux != NULL){
		if (strcmp(aux->mac,addr) == 0)
			return true;
		aux = aux->next;
	}
	return false;
}
