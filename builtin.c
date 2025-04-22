#include "main.h"

/**
 * builtin_exit - fonction to exit
 * @command: command to process
 * @env: environnement variables
 * @status: exit status
 */
void builtin_exit(char **command, char **env, int *status)
{
	(void)env;

	if (command[1] != NULL)
		*status = atoi(command[1]);
}

/**
 * builtin_printenv - fonction to print env
 * @command: command to process
 * @env: environnement variables
 * @status: exit status
 */
void builtin_printenv(char **command, char **env, int *status)
{
	int i = 0;
	(void)command;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}

	*status = 0;
}

/**
 * search_builtin - searches for a builtin command
 * @name: name of the command
 *
 * Return: function pointer
 */
void (*search_builtin(char *name))(char **command, char **env, int *status)
{
	int i = 0;

	builtin_t builtin[] = {
		{"exit", builtin_exit},
		{"env", builtin_printenv},
		{"printenv", builtin_printenv},
		{"setenv", builtin_setenv},
		{"unsetenv", builtin_unsetenv},
		{NULL, NULL}
	};

	while (builtin[i].name)
	{
		if (strcmp(name, builtin[i].name) == 0)
			break;
		i++;
	}

	return (builtin[i].fptr);
}
