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
 * get_env - gets an environment variable
 * @name: name of variable to get
 * @env: environment variable
 * @copy: buffer for the value
 *
 * Return: copy of the value of the environment variable
 */
char *get_env(const char *name, char **env, char *copy)
{
	int i = 0, cmp = 0;
	int number = 0;
	char *variable = NULL;
	char *value = NULL;
	char *environment[4096];

	memset(environment, 0, sizeof(environment));
	number = copy_env(env, environment);

	/* Searching for a matching variable */
	while (environment[i] != NULL)
	{
		variable = strtok(environment[i], "=\n");
		value = strtok(NULL, "=\n");

		cmp = strcmp(name, variable);

		if (cmp == 0 && value != NULL)
		{
			/* Copying and freeing */
			strcpy(copy, value);
			free_env(environment, number);
			return (copy);
		}

		i++;
	}

	free_env(environment, number);

	return (NULL);
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
 * get_arguments - separates the user input in an array of strings
 * @line: user input
 * @arguments: array of strings
 */
void get_arguments(char *line, char **arguments)
{
	int i = 0;
	char *string;

	string = strtok(line, " \n");

	if (string != NULL)
	{
		while (string != NULL)
		{
			/* Handling comments */
			if (string[0] == '#')
				break;

			arguments[i] = string;
			string = strtok(NULL, " \n");
			i++;
		}
	}
	else
		arguments[0] = NULL;
}

/**
 * process_command - process a given command
 * @arguments: command to process
 * @env: environment variables
 * @argv: arguments of the program
 * @status: exit status of the previous command
 *
 * Return: exit status of the command if found ; error code otherwise
 */

int process_command(char **arguments, char **env, char **argv, int status)
{
	pid_t child_pid;
	int code, i = 0;
	struct stat st;
	char copy[2048];

	/* Handling expansion */
	while (arguments[i] != NULL)
	{
		if (arguments[i][0] == '$' && arguments[i][1] == '?')
			sprintf(arguments[i], "%i", status);
		else if (arguments[i][0] == '$' && arguments[i][1] == '$')
			sprintf(arguments[i], "%i", getpid());
		else if (arguments[i][0] == '$' && arguments[i][1] != '\0')
			arguments[i] = get_env(&arguments[i][1], env, copy);
		i++;
	}

	/* Checking if the command exists */
	if (stat(arguments[0], &st) != 0)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", argv[0], arguments[0]);
		return (127);
	}

	child_pid = fork();

	if (child_pid == -1)
	{
		fprintf(stderr, "%s: fork failed\n", argv[0]);
		return (-1);
	}

	/* Executing the command */
	else if (child_pid == 0)
		execve(arguments[0], arguments, env);
	else
		wait(&code);

	return (WEXITSTATUS(code));
}
