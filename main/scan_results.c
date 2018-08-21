#include "scan_results.h"

scan_result *sc_rst;

void startScanResult(){
	sc_rst = NULL;
}

scan_result *getScanResult() {
	return sc_rst;
}

scan_result *newAddress(char *addr){
    scan_result *address = (scan_result *) malloc(sizeof(scan_result));
    address->addr = addr;
    address->next = NULL;
    return address;
}

/*
false
append 1:  f0:d7:aa:64:cf:8c
true: f0:d7:aa:64:cf:8c
true: f0:d7:aa:64:cf:8c
true: f0:d7:aa:64:cf:8c
true: f0:d7:aa:64:cf:8c
true: 6c:71:d9:03:4c:ac
true: f0:d7:aa:64:cf:8c
*/

void append(char *addr, void (* scanResultCallback)(char *addr)){
	scan_result *address = newAddress(addr);
    if (sc_rst == NULL){
        sc_rst = address;
        printf("append 1:  ");
    }
    else{
        scan_result *aux = sc_rst;
        while(sc_rst->next != NULL){
            sc_rst = sc_rst->next;
        }
		sc_rst->next = address;
		sc_rst = aux;
		printf("append N:  ");
    }
    scanResultCallback(address->addr);
}

int getSize(scan_result *sc_rst){
	scan_result *sc = sc_rst;
	int count = 0;
	while(sc->next != NULL){
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
		if(strcmp(aux->addr, addr) == 0){
			printf("true: %s\n",addr);
			return true;
		}
		aux = aux->next;
	}
	printf("false: ");
	return false;
}
