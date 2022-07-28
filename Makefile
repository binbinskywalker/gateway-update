home=/home/imx6/work/gateway-daemon
CC		=g++
DEBUG 		=-DUSE_DEBUG
CFLAGS		=-Wall -g
C_SOURCES	 	= $(wildcard  ./src/*.c)
INCLUDES  	= -I ./include -I ./include/curl
LIB_NAMES 	=  -lpthread -levent
LIB_PATH 	=-L ${home}/lib

OBJ		=$(patsubst %.c, %.o, $(C_SOURCES))
TARGET	=gateway-daemon

$(TARGET):$(OBJ)
	@mkdir -p build
	$(CC) $(OBJ) $(LIB_PATH) $(LIB_NAMES) -o build/$(TARGET)
	@rm -rf $(OBJ)

#compile
%.o: %.c
	$(CC) $(INCLUDES) $(DEBUG) -c $(CFLAGS) $< -o $@
%.o: %.cpp
	$(CC) $(INCLUDES) $(DEBUG) -c $(CFLAGS) $< -o $@

.PHONY:clean
clean:
	@echo "Remove linked and compiled files......"
	rm -rf $(OBJ) build/$(TARGET)
