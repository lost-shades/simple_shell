#include "main.h"

/**
 * display_tokens - function to show argc on terminal
 * @tokens: pointer to an array of string from user
 * @count: pointer to count argv
*/
void display_tokens(char *tokens[], int *count)
{
/* Display tokens */
int i;
for (i = 0; i < *count; i++)
{
printf("Token %d: %s\n", i, tokens[i]);
}
}

/**
 * tokeniz_input - function to tokenize user input
 * @input: string to be tokenized
 * @delim: user input separators
 * @tokens: pointer to an array of string from user
 * @token_count: pointer to count argv
*/
void tokeniz_input(char *input, char *delim, char *tokens[], int *token_count)
{
/* Tokenize input */
char *token = strtok(input, delim);
*token_count = 0;

while (token != NULL && *token_count < MAX_TOKENS)
{
tokens[*token_count] = strdup(token);
token = strtok(NULL, delim);
(*token_count)++;
}

tokens[*token_count] = NULL; /* Null-terminate the token array */
}

/**
 * execute_command - function to execute commands from user
 * @tokens: pointer to an array of string from user
*/
void execute_command(char *tokens[])
{
char *path_env, *path;
char *dir, *full_path;
pid_t pid = fork();

path_env = getenv("PATH");
path = strdup(path_env);

if (path_env == NULL || strlen(path_env) == 0)
{
perror("Error in PATH retrieval");
return;
}

if (pid == 0)
{
/*tokens[MAX_TOKENS - 1] = NULL;*/
if (execve(tokens[0], tokens, environ) == -1)
{
dir = strtok(path, ":");
while (dir != NULL)
{
full_path = malloc(strlen(dir) + strlen(tokens[0]) + 2);
sprintf(full_path, "%s/%s", dir, tokens[0]);
execve(full_path, tokens, environ);
free(full_path);
dir = strtok(NULL, ":");
}
perror("Error in execution");
exit(EXIT_FAILURE);
}
}
else if (pid < 0)
{
perror("Fork failed");
}
else
{
wait(NULL);
}
free(path);
}
