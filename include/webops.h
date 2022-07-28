#ifndef WEBOPS__H
#define WEBOPS__H

#include <common.h>
#include <stdio.h>

#define ACK_MSG_LEN 10
#define RECVBUFLEN 1024*1024
#define UDATE_FILE_NAME  "lora_pkt_fwd"

typedef struct configForWebServer{
    int serverPort;
    char *serverIP;
}WebServerConfig;

typedef struct infosForWebServer{
    char recvBuf[RECVBUFLEN];
    FILE *fp;
}WebServerParameter;

void *webServerToListen(void *args);
void configServerWeb(ConfigData *config, WebServerConfig *webConfig);

#endif