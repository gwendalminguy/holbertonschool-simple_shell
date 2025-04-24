#include "main.h"

/**
 * copy_env - copies all environment variables in an array of strings
 * @env: environment variables
 * @environment: destination
 */
void copy_env(char **env, char **environment)
{
	int i = 0;

	while (env[i] != NULL)
	{
		environment[i] = strdup(env[i]);
		i++;
	}
}

/**
 * free_env - frees an array of environment variables
 * @env: environment variables
 */
void free_env(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
}

/**
 * builtin_printenv - prints all environment variables
 * @p: parameters of the builtin command
 */
void builtin_printenv(parameters_t *p)
{
	int i = 0;

	while (p->environment[i] != NULL)
	{
		printf("%s\n", p->environment[i]);
		i++;
	}

	p->status = 0;
}

/**
 * builtin_setenv - adds or updates an environment variable
 * @p: parameters if the builtin command
 */
void builtin_setenv(parameters_t *p)
{
	int i = 0, m = 0, n = 0;
	int size = 0;

	if (p->command[1] != NULL && p->command[2] != NULL)
	{
		m = strlen(p->command[1]);
		n = strlen(p->command[2]);

		while (p->environment[i] != NULL)
		{
			if (strncmp(p->command[1], p->environment[i], m) == 0 && p->environment[i][m] == '=')
			{
				free(p->environment[i]);
				break;
			}

			i++;
		}

		size = m + n;

		p->environment[i] = malloc(size + 2);

		if (p->environment[i] == NULL)
		{
			fprintf(stderr, "%s: setenv failed\n", p->argv[0]);
			p->status = -1;
		}
		else
		{
			memset(p->environment[i], 0, size);
			sprintf(p->environment[i], "%s=%s", p->command[1], p->command[2]);
			p->status = 0;
		}
	}
	else
	{
		fprintf(stderr, "%s: setenv: missing argument\n", p->argv[0]);
		p->status = 99;
	}
}

/**
 * builtin_unsetenv - removes an environment variable
 * @p: parameters of the builtin commmand
 */
void builtin_unsetenv(parameters_t *p)
{
	int i = 0, n = 0;

	if (p->command[1] != NULL)
	{
		n = strlen(p->command[1]);
		while (p->environment[i] != NULL)
		{
			if (strncmp(p->command[1], p->environment[i], n) == 0)
				break;
			i++;
		}
		if (p->environment[i] == NULL)
		{
			fprintf(stderr, "%s: unsetenv: wrong argument\n", p->argv[0]);
			p->status = 99;
		}
		else
		{
			while (p->environment[i] != NULL)
			{
				free(p->environment[i]);
				if (p->environment[i + 1] != NULL)
				{
					p->environment[i] = malloc(1 + strlen(p->environment[i + 1]));
					strcpy(p->environment[i], p->environment[i + 1]);
				}
				else
				{
					p->environment[i] = NULL;
					p->status = 0;
				}
				i++;
			}
		}
	}
	else
	{
		fprintf(stderr, "%s: unsetenv: missing argument\n", p->argv[0]);
		p->status = 99;
	}
}
