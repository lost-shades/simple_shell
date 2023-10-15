#include "main.h"

void display_tokens(char *tokens[], int *count)
{
/* Display tokens */
int i;
for (i = 0; i < *count; i++)
{
printf("Token %d: %s\n", i, tokens[i]);
}
}

void tokenize_input(char *input, char *delimiter, char *tokens[], int *token_count)
{
/* Tokenize input */
char *token = strtok(input, delimiter);
*token_count = 0;

while (token != NULL && *token_count < MAX_TOKENS)
{
tokens[*token_count] = strdup(token);
token = strtok(NULL, delimiter);
(*token_count)++;
}

tokens[*token_count] = NULL; /* Null-terminate the token array */
}

void execute_command(char *tokens[])
{
char *path_env;
char *path;
char *dir;
char *full_path;

pid_t pid = fork();

if (pid == 0)
{
/* Child process */
/*tokens[MAX_TOKENS - 1] = NULL;*/

if (execve(tokens[0], tokens, environ) == -1)
{
path_env = getenv("PATH");

if (path_env == NULL)
{
perror("Error in PATH retrieval");
exit(EXIT_FAILURE);
}
path = strdup(path_env);
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
/* Parent process */
wait(NULL);
}
}


