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
 * @command: command to process
 * @env: environnement variables
 * @status: exit status
 * @argv: arguments of the program
 */
void builtin_printenv(char **command, char **env, int *status, char **argv)
{
	int i = 0;
	(void)command;
	(void)argv;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}

	*status = 0;
}

/**
 * builtin_setenv - adds or updates an environment variable
 * @command: command to process
 * @env: environment variables
 * @status: exit status
 * @argv: arguments of the program
 */
void builtin_setenv(char **command, char **env, int *status, char **argv)
{
	int i = 0, m = 0, n = 0;
	int size = 0;

	if (command[1] != NULL && command[2] != NULL)
	{
		m = strlen(command[1]);
		n = strlen(command[2]);

		while (env[i] != NULL)
		{
			if (strncmp(command[1], env[i], m) == 0)
			{
				free(env[i]);
				break;
			}

			i++;
		}

		size = m + n;

		env[i] = malloc(size + 2);

		if (env[i] == NULL)
		{
			fprintf(stderr, "%s: setenv failed\n", argv[0]);
			*status = -1;
		}
		else
		{
			memset(env[i], 0, size);
			sprintf(env[i], "%s=%s", command[1], command[2]);
			*status = 0;
		}
	}
	else
	{
		fprintf(stderr, "%s: setenv: missing argument\n", argv[0]);
		*status = 99;
	}
}

/**
 * builtin_unsetenv - removes an environment variable
 * @command: command to process
 * @env: environment variables
 * @status: exit status
 * @argv: arguments of the program
 */
void builtin_unsetenv(char **command, char **env, int *status, char **argv)
{
	int i = 0, n = 0;

	if (command[1] != NULL)
	{
		n = strlen(command[1]);
		while (env[i] != NULL)
		{
			if (strncmp(command[1], env[i], n) == 0)
				break;
			i++;
		}
		if (env[i] == NULL)
		{
			fprintf(stderr, "%s: unsetenv: wrong argument\n", argv[0]);
			*status = 99;
		}
		else
		{
			/* Freeing variable and shifting the others */
			while (env[i] != NULL)
			{
				free(env[i]);
				if (env[i + 1] != NULL)
				{
					env[i] = malloc(1 + strlen(env[i + 1]));
					if (env[i] == NULL)
					{
						fprintf(stderr, "%s: unsetenv failed\n", argv[0]);
						*status = -1;
						break;
					}
					strcpy(env[i], env[i + 1]);
				}
				else
				{
					env[i] = NULL;
					*status = 0;
				}
				i++;
			}
		}
	}
	else
	{
		fprintf(stderr, "%s: unsetenv: missing argument\n", argv[0]);
		*status = 99;
	}
}
