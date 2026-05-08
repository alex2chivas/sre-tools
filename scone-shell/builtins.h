#ifndef BUILTINS_H
#define BUILTINS_H

/* builtins - Handles running cd and exitting
 * run_cd: Handles moving directories
 * is_exit: Handles exiting the shell
*/ 

int run_cd(char *path);
int is_exit(char *cmd);

#endif
