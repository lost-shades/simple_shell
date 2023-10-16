#include "main.h"


void handle_exit(char *tokens[], int token_count)
{
/* 
Algorithm:
* If token_count == 1 or tokens[1] is NULL, exit with status 0.
* If token_count == 2, convert tokens[1] to int and exit with that status
*/

if (token_count == 1 || tokens[1] == NULL)
{
exit(0);
}
else if (token_count == 2)
{
int status = atoi(tokens[1]);
exit(status);
}
else
{
write(STDOUT_FILENO, "exit: too many args\n", strlen("exit: too many args\n"));
}
}

void handle_cd(char *tokens[], int token_count)
{
/*
* If token_count == 1 or tokens[1] is NULL, change to home using chdir(~)
* If token_count == 2, change to the specified dir using chdir(tokens[1])
*/
char cwd[1024];

if (token_count == 1 || tokens[1] == NULL || strcmp(tokens[1], "~") == 0)
{
if (chdir(getenv("HOME")) != 0)
perror("cd");
}
else if (strcmp(tokens[1], "-") == 0)
{
if (getenv("PWD") == NULL)
{
write(STDOUT_FILENO, "cd: PWD not set/n", strlen("cd: PWD not set/n"));
return;
}
if (chdir(getenv("PWD")) != 0)
perror("cd");
}
else if (token_count == 2)
{
if (chdir(tokens[1]) != 0)
perror("cd");
}
else
{
write(STDOUT_FILENO, "cd: too many arguments\n", strlen(25));
return;
}
if (getcwd(cwd, sizeof(cwd)) != NULL)
{
setenv("PWD", cwd, 1);
}
else
{
perror("getcwd");
}
}

void handle_env()
{
/* Print the environ var using the extern char **environ.*/
extern char **environ;
int i = 0;

while (environ[i] != NULL)
{
write(STDOUT_FILENO, environ[i], strlen(environ[i]));
write(STDOUT_FILENO, "\n", 1);
i++;
}
}

void handle_setenv(char *tokens[], int token_count)
{
/*
* If token_count is not 3, print an error message.
* Otherwise, use setenv function to set the environment variable.
*/
if (token_count != 3)
{
write(STDOUT_FILENO, "setenv: incorrect number of args\n", strlen(33));
return;
}
if (setenv(tokens[1], tokens[2], 1) != 0)
{
perror("setenv");
}
}

void handle_unsetenv(char *tokens[], int token_count)
{
/*
* If token_count is not 2, print an error message.
* Otherwise, use unsetenv function to unset the environment variable.
*/
if (token_count != 2)
{
write(STDOUT_FILENO, "unsetenv: incorrect number of args\n", strlen(35));
return;
}
if (unsetenv(tokens[1]) != 0)
{
perror("unsetenv");
}
}
