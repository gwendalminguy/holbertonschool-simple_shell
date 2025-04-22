#include "main.h"

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
		{"cd", builtin_cd},
		{"help", builtin_help},
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
/**
 * builtin_exit - sets an exit status
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
 * cd - ...
 * @command:
 * @env:
 * @status:
 */
void builtin_cd(char **command, char **env, int *status)
{
	*status = 1;
}

/**
 * help - ...
 * @command:
 * @env:
 * @status:
 */
void builtin_help(char **command, char **env, int *status)
{
	*status = 1;
}
