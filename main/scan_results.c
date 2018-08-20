#include "scan_results.h"

scan_result *create(){ //scan_result *sc_rst
	scan_result *sc_rst = (scan_result *) malloc (sizeof(scan_result));
	sc_rst->addr = "";
	sc_rst->next = NULL;
	return sc_rst;
}

scan_result *newAddress(char *addr){
    scan_result *address = (scan_result *) malloc(sizeof(scan_result));
    address->addr = addr;
    address->next = NULL;
    return address;
}

void append(scan_result **sc_rst, char *addr, void (* scanResultCallback)(char *addr)){
	scan_result *address = newAddress (addr);
    if ((*sc_rst) == NULL)
        (*sc_rst) = address;
    else{
        scan_result *aux = (*sc_rst);
        while(aux->next != NULL)
            aux = aux->next;
		aux->next = address;
		scanResultCallback(address->addr);
    }
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

void clearScanResult(scan_result *sc_rst){
	free(sc_rst);
}

bool exists(scan_result *sc_rst, char *addr){
	scan_result *sc = sc_rst;
	while(sc != NULL){
		if(sc->addr == addr){
			return true;
		}
		sc = sc->next;
	}
	return false;
}