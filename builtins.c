#include "main.h"

/**
 * handle_exit - function for builtin exit
 * @tokens: pointer to an array of string
 * @token_count: pointer to tokens counter
*/
void handle_exit(char *tokens[], int token_count)
{
/*
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

/**
 * handle_cd - function for builtin change directory
 * @tokens: pointer to an array of string
 * @token_count: pointer to tokens counter
*/
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
write(STDOUT_FILENO, "cd: too many args\n", strlen("cd: too many args\n"));
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

/**
 * handle_env - function for builtin env
 *@tokens: this shall rep tokens
 *@token_count: this shall rep nums oftokens
*/
void handle_env(__attribute__((unused))char *tokens[],
		__attribute__((unused))int token_count)
{
/* Print the environ var using the extern char **environ.*/
/*extern char **environ;*/
int i = 0;

while (environ[i] != NULL)
{
write(STDOUT_FILENO, environ[i], strlen(environ[i]));
write(STDOUT_FILENO, "\n", 1);
i++;
}
}

/**
 * handle_setenv - function for builtin setenv
 * @tokens: pointer to an array of string
 * @token_count: pointer to tokens counter
*/
void handle_setenv(char *tokens[], int token_count)
{
/*
* If token_count is not 3, print an error message.
* Otherwise, use setenv function to set the environment variable.
*/
if (token_count != 3)
{
write(STDOUT_FILENO, "wrong no of args\n", strlen("wrong no of args\n"));
return;
}
if (setenv(tokens[1], tokens[2], 1) != 0)
{
perror("setenv");
}
}

/**
 * handle_unsetenv - function for builtin unsetenv
 * @tokens: pointer to an array of string
 * @token_count: pointer to tokens counter
*/
void handle_unsetenv(char *tokens[], int token_count)
{
/*
* If token_count is not 2, print an error message.
* Otherwise, use unsetenv function to unset the environment variable.
*/
if (token_count != 2)
{
write(STDOUT_FILENO, "wrong no of args\n", strlen("wrong no of args\n"));
return;
}
if (unsetenv(tokens[1]) != 0)
{
perror("unsetenv");
}
}
