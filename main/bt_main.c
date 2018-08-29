#include "bluetooth.h"
#include "wifi.h"
//#include <curl/curl.h>

#define SA      struct sockaddr
#define MAXLINE 1000
#define MAXSUB  200


#define LISTENQ         1024

extern int h_errno;

char *json;

void result_callback(char *addr) {
	printf("Dispositivo encontrado: %s\n",addr);
}

ssize_t process_http(int sockfd, char *host, char *page, char *poststr) {
  char sendline[MAXLINE + 1], recvline[MAXLINE + 1];
  ssize_t n;
  snprintf(sendline, MAXSUB,
      "POST %s HTTP/1.1\r\n"
      "Host: %s\r\n"
      "Content-type: application/json\r\n"
      "Content-length: %d\r\n\r\n"
      "%s", page, host, strlen(poststr), poststr);
  printf("%s\n",sendline);

  write(sockfd, sendline, strlen(sendline));
  while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
    recvline[n] = '\r\n\0';
    printf("%s", recvline);
  }
  return n;
}

void post() {
  int sockfd;
  struct sockaddr_in servaddr;

  char **pptr;
  //********** You can change. Puy any values here *******
  char *hname = "192.168.2.104"; //
  char *page = ""; // /sensors/scan/Tokin
  char *poststr = "{\"timestamp\":535653656,\"devices\":\"5C:3E:2A:10:43:23\"}\r\n";

  //*******************************************************

  char str[50];
  struct hostent *hptr;

  hptr = gethostbyname(hname);
  if (hptr == NULL) {
    printf("Não foi possível encontrar %s\n",hname);
  }

  printf("hostname: %s\n", hptr->h_name);

  if ((hptr->h_addrtype == AF_INET) && ((pptr = hptr->h_addr_list) != NULL)) {
    printf("address: %s\n",inet_ntop(hptr->h_addrtype, *pptr, str,sizeof(str)));
  }

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  bzero(&servaddr, sizeof(servaddr));

  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(5000);
  
  inet_pton(AF_INET, str, &servaddr.sin_addr);
  connect(sockfd, (SA *) & servaddr, sizeof(servaddr));
  process_http(sockfd, hname, page, poststr);
  close(sockfd);
}


void app_main(void) {
    
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    if ((ret = esp_bt_controller_init(&bt_cfg)) != ESP_OK) {
        ESP_LOGE(GAP_TAG, "%s falha ao inicializar o controlador: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bt_controller_enable(ESP_BT_MODE_BTDM)) != ESP_OK) {
        ESP_LOGE(GAP_TAG, "%s falha ao ativar o controlador: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bluedroid_init()) != ESP_OK) {
        ESP_LOGE(GAP_TAG, "%s falha ao inicializar o bluedroid: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    if ((ret = esp_bluedroid_enable()) != ESP_OK) {
        ESP_LOGE(GAP_TAG, "%s falha ao ativar o bluedroid: %s\n", __func__, esp_err_to_name(ret));
        return;
    }

    initialize_wifi();
    //set_date_time();
    initialize_bt("BT_SAIL");
    get_paired_devices();
    set_date_and_time();
    
    while(true){
        start_scan(SCANTIME);
        json = get_JSON();
        if (json == NULL)
            exit(EXIT_FAILURE);
        else
            printf("%s\n",json);
        //send_data(json);
        post();
        free(json);
        delay(10); //Em segundos
    }
	
	
}

