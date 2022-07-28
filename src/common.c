
#include "cJSON.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <common.h>

bool readOutConfig(char *str, struct configData *config)
{
    cJSON *configstr;
	cJSON *serverPort;
	cJSON *serverIp;

	printf("config str:%s\n", str);
	configstr = cJSON_Parse(str);
	if(configstr == NULL){
		printf("nothing to parse\n");
		return false;
	}

	serverPort = cJSON_GetObjectItem(configstr, "serverport");
	serverIp = cJSON_GetObjectItem(configstr, "serverIP");

	if ( serverPort == NULL || serverIp == NULL){
		printf("parse config file failed\n");
		return false;
	}
	strncpy(config->serverIP, serverIp->valuestring, strlen(serverIp->valuestring));
	config->serverPort = serverPort->valueint;
	return true;
}

bool readConfig(ConfigData *config)
{
	FILE *fp;
	size_t readLen = 0;
	char buf[CONFIG_BUF_LEN] = {0};

	fp = fopen(CONFIG_PATH, "r+");
	if( fp == NULL){
		printf("fail to read config json\n");
		return false;
	}
	readLen = fread(buf, CONFIG_BUF_LEN, 1, fp);
	if(readLen < 0 ){
		printf("fail to read config\n");
	}
	fclose(fp);
	return readOutConfig(buf, config);
}
