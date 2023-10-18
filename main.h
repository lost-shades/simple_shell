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

/**
 * struct Builtin - name of builtin struct
 * @builtin_name: name of the builtin
 * @function: the function of the builtins
*/
typedef struct Builtin
{
char *builtin_name;
void (*function)(char *tokens[], int token_count);
} Builtin;

/**
 * struct Alias - name of the alias struct
 * @alias_name: name of alias
 * @main_name: the real name of the alias
*/
typedef struct Alias
{
char *alias_name;
char *main_name;
} Alias;

/* Alias aliases[MAX_TOKENS]; */

void handle_exit(char *tokens[], int token_count);
void handle_cd(char *tokens[], int token_count);
void handle_env(char *tokens[], int token_count);
void handle_setenv(char *tokens[], int token_count);
void handle_unsetenv(char *tokens[], int token_count);


/* extern char *builtins;*/
/* extern char *aliases;*/

void display_tokens(char *tokens[], int *count);
void tokeniz_input(char *input, char *delim, char *tokens[], int *token_count);
void execute_command(char *tokens[]);
int handle_builtins(char *tokens[], int *token_count);
void handle_alias(char *tokens[], int token_count);
void process_input(char *buff, char *delimiter, int *token_count);

#endif
