#include "main.h"

/**
 * copy_env - copies all environment variables in an array of strings
 * @env: environment variables
 * @environment: destination
 *
 * Return: number of variables
 */
int copy_env(char **env, char **environment)
{
	int i = 0;

	while (env[i] != NULL)
	{
		environment[i] = strdup(env[i]);
		i++;
	}

	return (i);
}

/**
 * free_env - frees an array of environment variables
 * @env: environment variables
 * @number: number of variables
 */
void free_env(char **env, int number)
{
	int i = 0;

	while (i < number)
	{
		if (env[i] != NULL)
		{
			free(env[i]);
			i++;
		}
	}
}

/**
 * builtin_printenv - prints all environment variables
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
 * builtin_setenv - adds or updates an environment variable
 * @command: command to process
 * @env: environment variables
 * @status: exit status
 */
void builtin_setenv(char **command, char **env, int *status)
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
				builtin_unsetenv(command, env, status);
			i++;
		}

		size = 2 + m + n;

		env[i] = malloc(size);

		if (env[i] == NULL)
		{
			fprintf(stderr, "hsh: setenv failed\n");
			*status = 99;
		}
		else
		{
			memset(env[i], 0, size);
			sprintf(env[i], "%s=%s", command[1], command[2]);
			env[i + 1] = NULL;
			*status = 0;
		}
	}
	else
	{
		fprintf(stderr, "hsh: setenv failed\n");
		*status = 99;
	}
}

/**
 * builtin_unsetenv - removes an environment variable
 * @command: command to process
 * @env: environment variables
 * @status: exit status
 */
void builtin_unsetenv(char **command, char **env, int *status)
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
			fprintf(stderr, "hsh: unsetenv failed\n");
			*status = 99;
		}
		else
		{
			while (env[i] != NULL)
			{
				env[i] = env[i + 1];
				i++;
			}

			*status = 0;
		}
	}
	else
	{
		fprintf(stderr, "hsh: unsetenv failed\n");
		*status = 0;
	}
}
