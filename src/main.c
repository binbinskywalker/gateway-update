#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <webops.h>
#include <common.h>
#include <stdio.h>
#include <string.h>

void Stop(int signo)
{
    printf("oops! stop gateway-daemon!!!\n");
    _exit(0);
}

int main()
{
	ConfigData config;
	WebServerConfig serverConfig;
	pthread_t tid;

	memset(&config, 0, sizeof(ConfigData));
	memset(&serverConfig, 0, sizeof(WebServerConfig));

	if(!readConfig(&config)){
		printf("fail to parse config file\n");
		return -1;
	}
	configServerWeb(&config,&serverConfig);

	if (pthread_create(&tid, NULL, webServerToListen, &serverConfig) == -1){
        printf("create thread gateway-daemon fail\n");
		return -1;
    }
	signal(SIGINT, Stop);
	while(1){
		sleep(10);
	}

    return 0;
}
