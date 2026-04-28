# scone-shell

A minimal Unix shell written in C. Demonstrates how shells work under the hood using fork, exec, and wait — the same system calls that bash uses to run every command.

## Compile

```bash
gcc -o scone-shell scone-shell.c
```

## Usage

```bash
./scone-shell
```

## Example

```
/home/alexisf scone-shell> ls -la
total 16
drwxr-xr-x. 2 alexisf alexisf 4096 Apr 28 10:50 .
drwxr-xr-x. 3 alexisf alexisf 4096 Apr 23 09:42 ..

/home/alexisf scone-shell> cd /tmp
/tmp scone-shell> pwd
/tmp

/tmp scone-shell> invalidcommand
Command not found: invalidcommand

/tmp scone-shell> exit
```

## Features

- Runs external commands with arguments (ls -la, cat file.txt, etc.)
- Built-in `cd` with directory validation
- Built-in `exit`
- Working directory displayed in prompt
- Error handling for invalid commands and empty input

## How it works

1. Print prompt with current directory
2. Read user input
3. Parse into arguments using strtok
4. Check for builtins (exit, cd) — handle without forking
5. Fork a child process
6. Child: exec the command (replaces itself with the program)
7. Parent: wait for child to finish
8. Loop back to step 1

## What I learned

- Process creation with fork()
- Program execution with execvp()
- Parent-child process relationships with wait()
- Built-in vs external command handling
- Why cd must be a shell builtin (child can't change parent's directory)
- Input parsing with strtok for variable-length arguments
