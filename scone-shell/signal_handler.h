#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

/*
 * handle_signal - Handles SIGINT and SIGTERM
 * SIGINT: prints fresh prompt (Ctrl+C)
 * SIGTERM: graceful shutdown
 */
void handle_signal(int sig);

#endif
