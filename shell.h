#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 4000
#define DELIM " \n\t\b"

int executor(char **arg, char *envp[]);
char **tokenizer(char *cmd);
char *_getenv(const char *name, char *envp[]);
char **path_const(char **arg, char *envp[]);
char *my_strdup(const char *str);
int _getline(char **cmd, size_t *cmd_len, FILE *stream);
int fill_buffer(FILE *stream, char *buff, size_t *bsize);
int allocate_buffer(char **cmd, size_t *cmd_len);
char *_strtok(char *str, const char *delim);
void rev_string(char *s);
char *_itoa(int n);
int print_error(char *argv[], char *cmd, int i);
void exit_shell(char *argv[]);
void print_env(char *envp[]);

#endif
