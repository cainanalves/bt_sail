#include "bluetooth.h"
#include "cJSON.h"

scan_result *sc_rst;

void start_scan_result() { sc_rst = NULL; }

scan_result *new_address(char *addr) {
    scan_result *newaddress = (scan_result *) malloc(sizeof(scan_result));
    strcpy(newaddress->mac,addr);
    newaddress->next = NULL;
    return newaddress;
}

void found_device(char *addr, void (* scan_result_callback)(char *addr)) {
	scan_result *newaddress = new_address(addr);
    if (sc_rst == NULL){
        sc_rst = newaddress;
    }else{
		newaddress->next = sc_rst->next;
    	sc_rst->next = newaddress;
    }
    scan_result_callback(newaddress->mac);
}

int get_size_scan_result() {
	scan_result *sc = sc_rst;
	int count = 0;
	while(sc != NULL){
		count++;
		sc = sc->next;
	}
	return count;
}

void clear_scan_result() { free(sc_rst); }

bool exists(char *addr) {
	scan_result *aux = sc_rst;
	while(aux != NULL){
		if (strcmp(aux->mac,addr) == 0)
			return true;
		aux = aux->next;
	}
	return false;
}

cJSON *create_JSON() {   
    cJSON *root = NULL;
    int length = get_size_scan_result();
    int pos = 0;
	char *devices[length];
	scan_result *aux = sc_rst;
    while(aux != NULL){
		devices[pos] = aux->mac;
		pos++;
		aux = aux->next;
    }
    root = cJSON_CreateObject();
    cJSON_AddStringToObject(root, "sensor", get_timestamp()); 
	cJSON_AddItemToObject(root, "mac", cJSON_CreateStringArray(devices, length));
	return root;
}

char *get_JSON() {
    char *out = NULL;
    cJSON *root = create_JSON();
    out = cJSON_PrintUnformatted(root);
    cJSON_Delete(root);
    return out;
}