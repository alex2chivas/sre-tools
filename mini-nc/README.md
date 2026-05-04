# mini-nc

A minimal TCP client written in C, similar to `netcat`. Connects to a host and port, then provides an interactive session for sending and receiving raw TCP data.

## Compile

```bash
gcc -o mini-nc mini-nc.c
```

## Usage

```bash
./mini-nc <ip> <port>
```

## Examples

Connect to a local SSH server:
```
./mini-nc 127.0.0.1 22
Socket created
Connected to 127.0.0.1:22
```

Chat with a netcat listener (terminal 1: `nc -l 9999`):
```
./mini-nc 127.0.0.1 9999
Socket created
Connected to 127.0.0.1:9999
> hello from mini-nc
```

## How it works

1. Create a TCP socket with socket()
2. Set up destination address (IP, port, IPv4)
3. Connect to the server with connect()
4. Interactive loop: read input, send to server, receive response
5. Close socket on disconnect

## What I learned

- TCP socket programming (socket, connect, send, recv, close)
- The sockaddr_in struct for network addressing
- Network byte order conversion with htons and inet_addr
- Blocking I/O behavior with recv
- Difference between raw TCP and application protocols (SSH, HTTP)
- Why netcat works with raw text but SSH requires a protocol handshake
