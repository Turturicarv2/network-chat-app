CC = gcc

# DIRECTORIES
BUILD_DIR = build

# FILES
SERVER_FILES = src/server.c
CLIENT_FILES = src/client.c

# TARGETS
all: server client

server: $(SERVER_FILES)
	mkdir -p $(BUILD_DIR)
	$(CC) $(SERVER_FILES) -o $(BUILD_DIR)/$@

client: $(CLIENT_FILES)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CLIENT_FILES) -o $(BUILD_DIR)/$@

clean:
	rm -rf $(BUILD_DIR)