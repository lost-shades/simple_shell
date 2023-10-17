#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stddef.h>

#define MAX_TOKENS 100
#define BUFFER_SIZE 1024

extern char **environ;

typedef struct
{
char *builtin_name;
void (*function)(char *tokens[], int token_count);
} Builtin;

typedef struct
{
char *alias_name;
char *main_name;
} Alias;

/* Alias aliases[MAX_TOKENS]; */

void handle_exit(char *tokens[], int token_count);
void handle_cd(char *tokens[], int token_count);
void handle_env(void);
void handle_setenv(char *tokens[], int token_count);
void handle_unsetenv(char *tokens[], int token_count);


/* extern char *builtins;*/
/* extern char *aliases;*/

void display_tokens(char *tokens[], int *count);
void tokeniz_input(char *input, char *delim, char *tokens[], int *token_count);
void execute_command(char *tokens[]);
void handle_builtins(char *tokens[], int *token_count);
void handle_alias(char *tokens[], int token_count);
void process_input(char *buff, char *delimiter, int *token_count);

#endif
