#include "main.h"

/**
 * builtin_exit - fonction to exit
 * @command: ...
 * @env: environnement variables
 * @status: ...
 */
void builtin_exit(char **command, char **env, int *status)
{
	if (command[1] != NULL)
		*status = atoi(command[1]);
}

/**
 * builtin_env - fonction to print env
 * @command: ...
 * @env: environnement variables
 * @status: ...
 */
void builtin_env(char **command, char **env, int *status)
{
	int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

/**
 * search_builtin - ...
 * @string: ...
 *
 * Return: ...
 */
void (*search_builtin(char *string))(char **command, char **env, int *status)
{
	int i = 0;

	builtin_t builtin[] = {
		{"exit", builtin_exit},
		{"env", builtin_env},
		{"printenv", builtin_env},
		{NULL, NULL}
	};

	while (builtin[i].name)
	{
		if (strcmp(string, builtin[i].name) == 0)
		{
			builtin[i].func;
			break;
		}
		i++;
	}

	return (builtin[i].func);
}

