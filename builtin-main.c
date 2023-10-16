#include "main.h"

void handle_alias(char *tokens[], int token_count)
{
char *alias_name; *main_name;
int i;
Alias aliases[MAX_TOKENS];

aliases[0].alias_name = "ll";
aliases[0].main_name = "ls -l";

if (token_count == 1)
{
for (i = 0; i < MAX_TOKENS && aliases[i].alias_name != NULL; i++)
{
write(STDOUT_FILENO, aliases[i].alias_name, strlen(aliases[i].alias_name));
write(STDOUT_FILENO, "='", 2);
write(STDOUT_FILENO, aliases[i].main_name, strlen(aliases[i].main_name));
write(STDOUT_FILENO, "'\n", 2);
}
return;
}
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

/**
 * handle_builtins - function that executes builtin commands
 * @tokens: pointer to an array of strings
 * @token_count: pointer to counter for tokens
*/

void handle_builtins(char *tokens[], int *token_count)
{
int i = 0;
Builtin builtins[] = {
{"exit", handle_exit},
{"cd", handle_cd},
{"env", handle_env},
{"setenv", handle_setenv},
{"unsetenv", handle_unsetenv},
{NULL, NULL}
};

while (builtins[i].builtin_name != NULL)
{
if (strcmp(tokens[0], builtins[i].builtin_name) == 0)
{
if (builtins[i].function != NULL)
{
builtins[i].function(tokens, *token_count);
break;
}
}
i++;
}
/*execute_command(tokens); ---Don't execute twice---*/
/* if not builtin, execute as a normal command*/
}
