CC = gcc

BUILD_DIR = build

SERVER_FILES = src/server.c
CLIENT_FILES = src/client.c

all: 

server: 
	mkdir -p $(BUILD_DIR)
	$(CC) $(SERVER_FILES) -o $(BUILD_DIR)/$@

client: 
	mkdir -p $(BUILD_DIR)
	$(CC) $(CLIENT_FILES) -o $(BUILD_DIR)/$@

clean:
	rm -rf $(BUILD_DIR)