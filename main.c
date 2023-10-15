#include "main.h"

void process_input(char *buff, char *delimiter, int *token_count)
{
char *tokens[MAX_TOKENS];
int i;

tokenize_input(buff, delimiter, tokens, token_count);
/* display_tokens(tokens, token_count); */
handle_builtins(tokens, token_count);
/*handle_alias (tokens, *token_count);  ---has problems*/
execute_command(tokens);

for (i = 0; i < *token_count; i++)
{
if (tokens[i] != NULL)
{
free(tokens[i]);
tokens[i] = NULL;
}
}
}

int main(int ac __attribute__((unused)), char **av __attribute__((unused)))
{
int int_mode = 1;
    char *buff = NULL;
    char *delimiter = " \t\n";
    size_t buffsize = 0;
    ssize_t user_input;
    /*int i; ---No need for it---*/

    /*char *tokens[MAX_TOKENS];  ---No need for it---*/
    int token_count = 0;

    while (int_mode)
    {
        int_mode = isatty(STDIN_FILENO);
        if (int_mode == 1)
	{
            write(STDOUT_FILENO, "~$ ", 3);
        }

        user_input = getline(&buff, &buffsize, stdin);

	if (user_input == -1)
	{
	/* handle EOF (Ctrl D) */
		break;
	}

        /* Tokenize the input command */


	process_input(buff, delimiter, &token_count);
        if (buff != NULL)
        {
	        free(buff);
	        buff = NULL;
        }
        else
        {
                break;
        }

        /* Execute the command using execve() 
	execute_command(tokens);  ---Tokens not available here*/

        /* Clean up memory  ---No need for it everythin in process input function---
	for (i = 0; i < token_count; i++)
	{
		if (tokens[i] != NULL)
		{
			free(tokens[i]);
			tokens[i] = NULL;
		}
	}*/
    }
    if (buff != NULL)
    {
	    free(buff);
	    buff = NULL;
    }

    return (0);
}

