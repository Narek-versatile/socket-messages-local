# Socket Messages Local

A simple socket-based messaging application written in C for Linux/WSL. This project demonstrates basic TCP/IP communication between a server and a client within a local network or on the same machine.

## Features

- **TCP/IP Sockets**: Uses standard POSIX socket API (`sys/socket.h`).
- **Real-time Messaging**: Send text messages from the client to the server.
- **Cross-WSL Communication**: Can communicate between different WSL instances or between WSL and other Linux machines on the network.

## Files

- `server.c`: Listens for incoming connections on port 8080 and prints received messages.
- `wsl_client.c`: Connects to a specified server IP and allows the user to send messages.

## Prerequisites

- GCC compiler
- A Linux environment (WSL, Ubuntu, etc.)

## Getting Started

### 1. Compile the Server and Client

Open your terminal and run:

```bash
gcc server.c -o server
gcc wsl_client.c -o client
```

### 2. Run the Server

Start the server first:

```bash
./server
```

The server will display its listening status and wait for a connection.

### 3. Run the Client

In another terminal (or another WSL tab), start the client:

```bash
./client
```

1. Enter the Server's IP address when prompted (use `127.0.0.1` if running on the same machine).
2. Start typing messages.
3. Type `exit` to close the connection.

## License

MIT
