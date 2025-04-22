#include "main.h"

/**
 * builtin_exit - fonction to exit
 * @env: environnement
 */

void builtin_exit(char **env)
{
	(void)env;
	exit(0);
}

/**
 * builtin_env - fonction to print env
 * @env: environnement
 */

void builtin_env(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}


int (*search_builtin(char *string))(char **command)
{
	int i = 0;

	builtin_t builtin[] = {
		{"exit", builtin_exit},
		{"env", builtin_env},
		{NULL, NULL}
	};

	while (builtin[i].name)
	{
		if (strcmp(command[0], builtin[i].name) == 0)
		{
			builtin[i].func;		
			break;
		}
		i++;
	}
	
	return (builtin[i].func);
}

void builtin_exit(char **env);
void builtin_env(char **env);
