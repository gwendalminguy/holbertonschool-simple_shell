#include "main.h"

/**
 * builtin_exit - fonction to exit
 * @env: environnement
 */

void builtin_exit(char **command, char **env, int status)
{
	(void)env;
	(void)command;
	(void)status;
	exit(0);
}

/**
 * builtin_env - fonction to print env
 * @env: environnement
 */

void builtin_env(char **command, char **env, int status)
{
	int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}


void (*search_builtin(char *string))(char **command, char **env, int status)
{
	int i = 0;

	builtin_t builtin[] = {
		{"exit", builtin_exit},
		{"env", builtin_env},
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

