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
	char *macs[length];
	scan_result *aux = sc_rst;
    while(aux != NULL){
		macs[pos] = aux->mac;
		printf("mac %d: %s\n",pos,macs[pos]);
		pos++;
		aux = aux->next;
    }
    root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "timestamp", get_timestamp()); 
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

    len = strlen(out) + 5;
    buf = (char*)malloc(len);
    if (buf == NULL)
    {
        printf("Falha ao alocar memória.\n");
        exit(1);
    }

    len_fail = strlen(out);
    buf_fail = (char*)malloc(len_fail);
    if (buf_fail == NULL)
    {
        printf("Falha ao alocar memória.\n");
        exit(1);
    }

    if (!cJSON_PrintPreallocated(root, buf, (int)len, 1)) {
        printf("cJSON_PrintPreallocated falhou!\n");
        if (strcmp(out, buf) != 0) {
            printf("cJSON_PrintPreallocated não é o mesmo que cJSON_Print!\n");
            printf("Resultado de cJSON_Print:\n%s\n", out);
            printf("Resultado de cJSON_PrintPreallocated:\n%s\n", buf);
        }
        free(out);
        free(buf_fail);
        free(buf);
        return NULL;
    }

    if (cJSON_PrintPreallocated(root, buf_fail, (int)len_fail, 1)) {
        printf("cJSON_PrintPreallocated falhou ao mostrar o erro com memória insuficiente!\n");
        printf("Resultado de cJSON_Print:\n%s\n", out);
        printf("Resultado de cJSON_PrintPreallocated:\n%s\n", buf_fail);
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