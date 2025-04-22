#include "main.h"

/**
 * print_env - prints all environment variables
 * @env: environment variables
 */
void print_env(char **env)
{
	int i = 0;

	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
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

	memset(env[i], 0, size);

	sprintf(env[i], "%s=%s", command[1], command[2]);

	env[i + 1] = NULL;

	*status = 0;
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
