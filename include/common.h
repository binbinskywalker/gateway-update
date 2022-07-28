#ifndef __COMMON__H
#define __COMMON__H

#include <stdbool.h>

#define CONFIG_PATH  "config.json"
#define CONFIG_BUF_LEN 10240

typedef struct configData{
    int serverPort;
    char serverIP[20];
}ConfigData;

bool readConfig(ConfigData *config);

#endif