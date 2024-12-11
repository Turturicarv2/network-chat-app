# Simple TCP Chat Application

## What the Project Does

This is a simple TCP-based chat application that supports multiple clients. It allows users to connect to a central server and exchange messages in real-time. The project is split into two main components:

1. **Server**: Handles client connections and relays messages between clients.
2. **Client**: Connects to the server and enables users to send and receive messages.

The server supports up to 2 simultaneous clients by default, but this can be modified in the source code.

---

## How to Get Started

### Prerequisites
- A C compiler (e.g., `gcc`)
- A Unix-based environment (Linux/macOS or WSL on Windows)

### Setting Up
1. **Clone the Repository**:
```
git clone https://github.com/Turturicarv2/network-chat-app.git
cd network-chat-app
```

2. **Build the Application: Use the provided Makefile to compile both the server and client**:
```
make
```
This will generate `server` and `client` binaries in the `build` directory.

3. **Run the Server: Start the server to listen for client connections**:
```
./build/server
```

4. **Run the Client(s): Start one or more clients to connect to the server**:
```
./build/client
```

### Usage
- Once a client connects, they can start sending messages to the server.
- Messages are relayed to all connected clients.
- To leave the chat, type `exit` and press Enter.

### Cleanup
To remove the built binaries, use:
```
make clean
```

---
## License

This project is open source and licensed under the [MIT](https://choosealicense.com/licenses/mit/) License.