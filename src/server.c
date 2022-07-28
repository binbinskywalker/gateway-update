#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "event2/util.h"
#include "event2/http.h"
#include "event2/event.h"
#include "event2/buffer.h"
#include "event2/http_struct.h"
#include "cJSON.h"
#include "stdbool.h"
#include <webops.h>
#include <common.h>

void generic_cb(struct evhttp_request* req, void* arg);
bool checkFile( char *recv);
bool saveFile(WebServerParameter *paras);
bool updateFile(WebServerParameter *paras);

WebServerParameter paras;

void configServerWeb(ConfigData *config, WebServerConfig *webConfig)
{
	webConfig->serverPort = config->serverPort;
	webConfig->serverIP = config->serverIP;
}

void *webServerToListen(void *args)
{
	WebServerConfig *p = (WebServerConfig*)args;

    paras.fp = NULL;
    memset(paras.recvBuf, '\0', RECVBUFLEN);

   	short http_port = p->serverPort;
    char* http_addr = p->serverIP;

    struct event_base* base = event_base_new();
    struct evhttp* http_server = evhttp_new(base);
    if(NULL == http_server)
    {
        return NULL;
    }

    int ret = evhttp_bind_socket(http_server, http_addr, http_port);
    if(ret != 0)
    {
        return NULL;
    }

    evhttp_set_gencb(http_server, generic_cb, NULL);
    printf("http server start OK!\n");
    event_base_dispatch(base);
    evhttp_free(http_server);
    return 0;
}

void generic_cb(struct evhttp_request* req, void* arg)
{
	char ack[ACK_MSG_LEN];
	struct evbuffer *eachbuf;

	eachbuf = evhttp_request_get_input_buffer(req);
	while (evbuffer_get_length(eachbuf)) {
		evbuffer_remove(eachbuf, paras.recvBuf, RECVBUFLEN);
	}
    printf("recv:%s\n", paras.recvBuf);

    if (checkFile(paras.recvBuf)){
        if(saveFile(&paras)){
            if(updateFile(&paras)){
                strncpy(ack,"true",5);
                evbuffer_add(req->output_buffer, ack, strlen(ack));
                evhttp_send_reply(req, 200, "OK", NULL);
                return;
            }
        }
	}
    strncpy(ack,"false",6);
    evbuffer_add(req->output_buffer, ack, strlen(ack));
    evhttp_send_reply(req, 404, "FALSE", NULL);
}

bool checkFile( char *recv)
{

    return true;
}

bool saveFile(WebServerParameter *paras)
{
    paras->fp = fopen(UDATE_FILE_NAME, "w+");
    if (paras->fp != NULL){
        fprintf(paras->fp, paras->recvBuf);
        fclose(paras->fp);
        return true;
    }
    return false;
}

bool updateFile(WebServerParameter *paras)
{
    char commond[256];
    pid_t status;

    snprintf(commond, 256, "%s %s", "./update.sh", UDATE_FILE_NAME);
    status = system(commond);
    if (-1 == status)
    {
        printf("update file error!");
        return false;
    }else {
        printf("exit status value = [0x%x]\n", status);
        if (WIFEXITED(status))
        {
            if (0 == WEXITSTATUS(status))
            {
                printf("run shell script successfully.\n");
            }else{
                printf("run shell script fail, script exit code: %d\n", WEXITSTATUS(status));
                return false;
            }
        }else{
            printf("exit status = [%d]\n", WEXITSTATUS(status));
        }
    }
    return true;
}