#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_LENGTH 100

extern char **env;

void handle_cmd(char *cmd, char *arg);
void parse_input(char *input, char **cmd, char **arg);
ssize_t _get_line(char **lineptr, size_t *n, FILE *stream);
void *alloc_mem(size_t size);
void *realloc_mem(void *ptr, size_t size);
void free_mem(void *ptr);
void refill_buf(char **buffer, size_t *p, size_t *size, FILE *stream);
size_t write_to_line(char buffer[], size_t *p,
		char **lineptr, size_t *n, size_t i);
void handle_exit(char *arg);
void handle_env(void);
void handle_setenv(char *variable, char *value);
void handle_unsetenv(char *variable);
void handle_cd(char *dir);

#endif
