# scone-shell

A minimal Unix shell written in C. Demonstrates how shells work under the hood using fork, exec, wait, pipes, and signal handling — the same system calls bash uses for every command you run.

## Project Structure

```
scone-shell.c        Main loop, input parsing, pipe detection
signal_handler.c/h   SIGINT and SIGTERM handling
builtins.c/h         cd and exit builtins
executor.c/h         fork/exec/wait for single commands
pipe_executor.c/h    Pipe support (cmd1 | cmd2)
Makefile             Build automation
```

## Compile

```bash
make scone-shell
```

Or manually:

```bash
gcc -o scone-shell scone-shell.c signal_handler.c builtins.c executor.c pipe_executor.c
```

## Usage

```bash
./scone-shell
```

## Example

```
/home/user scone-shell> ls -la
total 16
drwxr-xr-x. 2 user user 4096 Apr 28 10:50 .
drwxr-xr-x. 3 user user 4096 Apr 23 09:42 ..

/home/user scone-shell> ls -la | grep .c
-rw-r--r--. 1 user user  341 May  6 07:03 builtins.c
-rw-r--r--. 1 user user  285 May  8 12:02 executor.c

/home/user scone-shell> cd /tmp
/tmp scone-shell> exit
```

## Features

- Runs external commands with arguments (ls -la, cat file.txt, etc.)
- Pipe support for two commands (cmd1 | cmd2)
- Built-in `cd` with directory validation
- Built-in `exit`
- Working directory displayed in prompt
- Error handling for invalid commands and empty input
- Signal handling (SIGINT, SIGTERM)
- Ctrl+C doesn't kill the shell, graceful shutdown on SIGTERM

## How it works

For a normal command:

1. Print prompt with current directory
2. Read user input
3. Parse into arguments using strtok
4. Check for builtins (exit, cd) — handle without forking
5. Fork a child process via executor module
6. Child: exec the command (replaces itself with the program)
7. Parent: wait for child to finish

For a piped command (cmd1 | cmd2):

1. Detect '|' in input before parsing
2. Split input on '|', then split each side on spaces
3. Create a pipe with pipe()
4. Fork once for cmd1 — redirect stdout to pipe write end with dup2
5. Fork again for cmd2 — redirect stdin from pipe read end with dup2
6. Both children exec their commands
7. Parent closes both pipe ends and waits for both children

## What I learned

- Process creation with fork()
- Program execution with execvp()
- Parent-child process relationships with wait()
- Built-in vs external command handling
- Why cd must be a shell builtin (child can't change parent's directory)
- Input parsing with strtok for variable-length arguments
- Signal handling with signal() and custom handler functions
- How signal registration persists in the kernel for the life of the process
- fflush(stdout) to force buffered output to screen
- Pipe creation and bidirectional file descriptors (read end / write end)
- File descriptor redirection with dup2()
- Why dup2 must come before close in the redirection sequence
- Multi-file C project structure with header files
- Separating declarations (.h) from definitions (.c)
- Using extern for variables shared across files
- Building multi-file projects with Makefile
