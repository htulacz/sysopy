CC=gcc
BUILD_DIR=build

BUILD := debug

cflags.common := -std=c11 -Wall 
cflags.debug := -g -O0 
cflags.release := -O2
CFLAGS := ${cflags.${BUILD}} ${cflags.common}

.PHONY: all clean

all: client server

client: client.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $<

server: server.c
	rm -rf /dev/mqueue/*
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $<

run_client: client 
	./$(BUILD_DIR)/client

run_server: server
	./$(BUILD_DIR)/server
	
clean:
	rm -f /dev/mqueue/*
	rm -rf $(BUILD_DIR)