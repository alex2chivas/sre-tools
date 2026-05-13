# port-scanner

A multi-threaded TCP port scanner written in C. Scans a range of ports on a target IP by spawning one thread per port and attempting a TCP connect to each. Ports that accept the connection are reported as OPEN.

## Compile

```bash
gcc -o port-scanner port-scanner.c -lpthread
```

Note the `-lpthread` flag — required for linking the POSIX threads library.

## Usage

```bash
./port-scanner <ip> <start_port> <end_port>
```

## Examples

Scan localhost:

```
./port-scanner 127.0.0.1 20 10000
Port 22 is OPEN
Port 111 is OPEN
Port 631 is OPEN
Port 3306 is OPEN
Port 9993 is OPEN
```

Scan a remote machine:

```
./port-scanner 10.10.10.145 20 10000
Port 22 is OPEN
Port 902 is OPEN
Port 3389 is OPEN
```

## How it works

1. Parse the IP and port range from command line arguments
2. Allocate arrays for thread handles and scan data structs
3. For each port in the range:
   - Build a scan_data struct with the IP and port
   - Spawn a thread running scan_port with that struct
4. Wait for all threads to finish with pthread_join

Each worker thread:

1. Creates a TCP socket
2. Attempts to connect to the target IP and port
3. If connect succeeds, prints the port as OPEN
4. Closes the socket and exits

## Performance

Multi-threading makes this fast against responsive hosts. Scanning 25,000 ports on localhost typically completes in about 1 second compared to hours sequentially.

## Limitations

- TCP connect scan only — no SYN scan, OS fingerprinting, or service detection
- Hangs on firewalled ports that silently drop packets (75 second OS timeout per port)
- No thread pool limit — spawns one thread per port

For production use, tools like `nmap` use raw SYN packets and non-blocking sockets to avoid the timeout issue. This scanner is for learning the underlying concepts.

## What I learned

- Multi-threading with pthread (pthread_create, pthread_join)
- Passing structs as void * arguments to threads
- Casting void * back to the original type inside the worker
- Why pthread can only accept one argument and how to work around it
- Parallel TCP connect scanning
- Linking external libraries at compile time (-lpthread)
- Trade-offs between thread-per-task and thread pools
