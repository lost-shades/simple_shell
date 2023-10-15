#include "main.h"


void handle_exit(char *tokens[], int token_count)
{
/* Algorithm:
* 1. If token_count == 1 or tokens[1] is NULL, exit with status 0.
* 2. If token_count == 2, convert tokens[1] to an integer and exit with that statu.
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
/* Algorithm:
* If token_count == 1 or tokens[1] is NULL, change to the home dir using chdir("~").
* If token_count == 2, change to the dir specified in tokens[1] using chdir(tokens[1]).
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
write(STDOUT_FILENO, "cd: too many arguments\n", strlen("cd: too many arguments\n"));
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
/* Algorithm:
* Print the environment variables using the extern char **environ.
*/

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
/* Algorithm:
* If token_count is not 3, print an error message.
* Otherwise, use setenv function to set the environment variable.
*/
if (token_count != 3)
{
write(STDOUT_FILENO, "setenv: incorrect number of arguments\n", strlen("setenv: incorrect number of arguments\n"));
return;
}
if (setenv(tokens[1], tokens[2], 1) != 0)
{
perror("setenv");
}
}

void handle_unsetenv(char *tokens[], int token_count)
{
/* Algorithm:
* If token_count is not 2, print an error message.
* Otherwise, use unsetenv function to unset the environment variable.
*/
if (token_count != 2)
{
write(STDOUT_FILENO, "unsetenv: incorrect number of arguments\n", strlen("unsetenv: incorrect number of arguments\n"));
return;
}
if (unsetenv(tokens[1]) != 0)
{
perror("unsetenv");
}
}
void handle_alias (char *tokens[], int token_count)
{
char *alias_name;
char *main_name;
int i;
Alias aliases[MAX_TOKENS];

aliases[0].alias_name = "ll";
aliases[0].main_name = "ls -l";

if (token_count == 1)
{
/* Print all aliases if no specific alias is given */
for (i = 0; i < MAX_TOKENS && aliases[i].alias_name != NULL; i++)
{
write(STDOUT_FILENO, aliases[i].alias_name, strlen(aliases[i].alias_name));
write(STDOUT_FILENO, "='", 2);
write(STDOUT_FILENO, aliases[i].main_name, strlen(aliases[i].main_name));
write(STDOUT_FILENO, "'\n", 2);
}
return;
}

/* Check if the provided alias is defined */
alias_name = tokens[1];
main_name = NULL;

for (i = 0; i < MAX_TOKENS && aliases[i].alias_name != NULL; i++)
{
if (strcmp(alias_name, aliases[i].alias_name) == 0)
{
main_name = aliases[i].main_name;
break;
}
}

if (main_name != NULL)
{
/* Print the alias and its real command */
write(STDOUT_FILENO, alias_name, strlen(alias_name));
write(STDOUT_FILENO, "='", 2);
write(STDOUT_FILENO, main_name, strlen(main_name));
write(STDOUT_FILENO, "'\n", 2);
}
else
{
write(STDOUT_FILENO, "Alias not found.\n", strlen("Alias not found.\n"));
}
}
