#include "bluetooth.h"
#include "cJSON.h"

//Estrutura para resultado do escaneamento.
scan_result *sc_rst;


void create_scan_result() { sc_rst = NULL; }

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

	//Notificando MAC encontrado
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

//Cria estrutura JSON
cJSON *create_JSON() {   
	//Objeto JSON
    cJSON *root = NULL;
	//Pega-se a quantidade de dispositivos escaneados.
    int length = get_size_scan_result();
    int pos = 0;
	//Cria-se uma lista de dispositivos para ser estruturada no JSON.
	char *devices[length];
	//Estrutura auxiliar usada para percorrer a principal e adicionar os MACs na lista criada.
	scan_result *aux = sc_rst;
    while(aux != NULL){
		devices[pos] = aux->mac;
		pos++;
		aux = aux->next;
    }
	//Objeto JSON criado
    root = cJSON_CreateObject();
	
	//Estruturação dos dados do JSON (consultar ' https://github.com/DaveGamble/cJSON ' para melhor compreensao).
	//Estrutura sujeita a mudanças a qualquer momento, favor consultar o desenvolvedor
	//do backend que irá receber os dados. (araujobd)
	cJSON_AddNumberToObject(root,"sensor_id",1);
    cJSON_AddStringToObject(root, "timestamp", get_timestamp()); 
	cJSON_AddItemToObject(root, "macs", cJSON_CreateStringArray(devices, length));
	return root;
}

char *get_JSON() {
	//
    char *out = NULL;
	//Criando estrutura dos dados em formato JSON
    cJSON *root = create_JSON();
	//Gerando saída sem formatação, para economizar espaços no envio dos dados
    out = cJSON_PrintUnformatted(root);
	//Limpando a memória 
    cJSON_Delete(root);
    return out;
}
