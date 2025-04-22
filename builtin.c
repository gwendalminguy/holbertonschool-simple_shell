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

builtin_t builtin[] = {
	{"exit", builtin_exit},
	{"env", builtin_env},
	{NULL, NULL}
};

i = 0;
		while (builtin[i].name)
		{
			if (strcmp(arguments[0], builtin[i].name) == 0)
			{
				builtin[i].func(env);
				break;
			}
			i++;
		}
		if (builtin[i].name != NULL)
		{
			continue;
		}

void builtin_exit(char **env);
void builtin_env(char **env);