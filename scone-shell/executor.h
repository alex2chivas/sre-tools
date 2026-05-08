#ifndef EXECUTOR_H
#define EXECUTOR_H

/*
 * run_command - Forks a child process and executes the command.
 * Parent waits for the child to finish.
 * args: NULL-terminated array of command and arguments
*/
void run_command(char *args[]);

#endif
