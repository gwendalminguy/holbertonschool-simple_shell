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
 * set_env - adds or updates an environment variable
 * @variable: name of the variable
 * @value: value of the variable
 * @env: environment variables
 * @argv: arguments of the program
 *
 * Return: 0 if successful ; -1 otherwise
 */
int set_env(char *variable, char *value, char **env, char **argv)
{
	int i = 0, m = 0, n = 0;
	int size = 0;

	m = strlen(variable);
	n = strlen(value);

	while (env[i] != NULL)
	{
		if (strncmp(variable, env[i], m) == 0)
			unset_env(variable, env, argv);
		i++;
	}

	size = 2 + m + n;

	env[i] = malloc(size);

	if (env[i] == NULL)
	{
		fprintf(stderr, "%s: setenv failed\n", argv[0]);
		return (-1);
	}

	memset(env[i], 0, size);

	sprintf(env[i], "%s=%s", variable, value);

	env[i + 1] = NULL;

	return (0);
}

/**
 * unset_env - removes an environment variable
 * @variable: name of the variable
 * @env: environment variables
 * @argv: arguments of the program
 *
 * Return: 0 if successful ; -1 otherwise
 */
int unset_env(char *variable, char **env, char **argv)
{
	int i = 0, n = 0;

	n = strlen(variable);

	while (env[i] != NULL)
	{
		if (strncmp(variable, env[i], n) == 0)
			break;
		i++;
	}

	if (env[i] == NULL)
	{
		fprintf(stderr, "%s: unsetenv failed\n", argv[0]);
		return (-1);
	}
	else
	{
		while (env[i] != NULL)
		{
			env[i] = env[i + 1];
			i++;
		}

		return (0);
	}
}

void builtin_exit(char **env)
{
	(void)env;
	exit(0);
}

void builtin_env(char **env)
{
	int i = 0;
	int len = 0;

	while (env[i])
	{
		len = strlen(env[i]);
		write(STDOUT_FILENO, env[i], len);
		write(STDOUT_FILENO, "\n", 1);
		i++;
	}
}