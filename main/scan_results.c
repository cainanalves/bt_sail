#include "scan_results.h"

scan_result *sc_rst;

void start_scan_result() { sc_rst = NULL; }

void print_scan_result() {
	scan_result *aux = sc_rst;
	while(aux != NULL){
		printf("%s\n",aux->mac);
		aux = aux->next;	
	}
}

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
    int length = get_size_scan_result(), pos = 0;
    char *macs[length];

    root = cJSON_CreateObject();
    scan_result *aux = sc_rst;
    
    while(aux != NULL){
		macs[pos] = aux->mac;
		pos++;
		aux = aux->next;
    }
    cJSON_AddNumberToObject(root, "exemplo de timestamp", 87874425454); // Obs: Atribuir o TIMESTAMP!!
	cJSON_AddItemToObject(root, "mac", cJSON_CreateStringArray(macs, length));
    
	return root;
}

char *get_JSON() {
    
    char *out = NULL;
    char *buf = NULL;
    char *buf_fail = NULL;
    size_t len = 0;
    size_t len_fail = 0;

    cJSON *root = create_JSON();
    out = cJSON_Print(root);

    /* the extra 5 bytes are because of inaccuracies when reserving memory */
    len = strlen(out) + 5;
    buf = (char*)malloc(len);
    if (buf == NULL)
    {
        printf("Failed to allocate memory.\n");
        exit(1);
    }

    len_fail = strlen(out);
    buf_fail = (char*)malloc(len_fail);
    if (buf_fail == NULL)
    {
        printf("Failed to allocate memory.\n");
        exit(1);
    }

    /* Print to buffer */
    if (!cJSON_PrintPreallocated(root, buf, (int)len, 1)) {
        printf("cJSON_PrintPreallocated failed!\n");
        if (strcmp(out, buf) != 0) {
            printf("cJSON_PrintPreallocated not the same as cJSON_Print!\n");
            printf("cJSON_Print result:\n%s\n", out);
            printf("cJSON_PrintPreallocated result:\n%s\n", buf);
        }
        free(out);
        free(buf_fail);
        free(buf);
        return NULL;
    }

    /* force it to fail */
    if (cJSON_PrintPreallocated(root, buf_fail, (int)len_fail, 1)) {
        printf("cJSON_PrintPreallocated failed to show error with insufficient memory!\n");
        printf("cJSON_Print result:\n%s\n", out);
        printf("cJSON_PrintPreallocated result:\n%s\n", buf_fail);
        free(out);
        free(buf_fail);
        free(buf);
        return NULL;
    }

    free(out);
    free(buf_fail);
    //free(buf);
    cJSON_Delete(root);
    return buf;
}