#include "main.h"


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
