#ifndef PIPE_EXECUTOR_H
#define PIPE_EXECUTOR_H

/*
 * run_piped_command - Executes two commands connected by a pipe (cmd1 | cmd2)
 * Splits input on '|', creates a pipe, forks twice, redirects stdout of the
 * first command and stdin of the second command through the pipe.
 *
 * input: full command string containing a pipe character
*/
void run_piped_command(char *input);

#endif
