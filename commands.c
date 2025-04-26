#include "main.h"

/**
 * free_array - frees an array
 * @array: array to free
 */
void free_array(char **array)
{
	int i = 0;

	while (i < 4096 && array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
}

/**
 * get_arguments - separates the user input in an array of strings
 * @line: user input
 * @env: environment variables
 * @p: parameters
 */
void get_arguments(char *line, char **env, parameters_t *p)
{
	int i = 0, j = 0;
	char *string;

	/* Writing user input in history */
	while (p->history[i] != NULL)
	{
		i++;
		if (i == 4096)
		{
			export_history(env, p);
			free_array(p->history);
			i = 0;
		}
	}

	p->history[i] = strdup(line);

	memset(p->command, 0, 4096);

	string = strtok(line, " \n");

	if (string != NULL)
	{
		while (string != NULL)
		{
			/* Handling comments */
			if (string[0] == '#')
				break;

			p->command[j] = string;
			string = strtok(NULL, " \n");
			j++;
		}
	}
	else
		p->command[0] = NULL;
}

/**
 * get_integer - converts a string into an integer
 * @str: string to convert
 *
 * Return: integer if successful ; -1 otherwise
 */
int get_integer(char *str)
{
	int i;
	int length = strlen(str);
	int sign = 1, number = 0;
	int start = -1, end = 0;

	if (length == 1 && str[0] == 0)
		return (0);

	/* Getting the sign, the starting index and the ending index */
	for (i = 0 ; i < length ; i++)
	{
		if (str[i] == '-')
			sign = -sign;
		if ((str[i] >= 48 && str[i] <= 57) && (str[i - 1] < 48 || str[i - 1] > 57))
			start = i;
		if ((str[i] >= 48 && str[i] <= 57) && (str[i + 1] < 48 || str[i + 1] > 57))
		{
			end = i;
			break;
		}
	}

	/* Going through each digit and updating the number to return */
	if (start >= 0)
	{
		for (i = start ; i <= end ; i++)
			number = number * 10 + (str[i] - 48);

		if (sign < 0)
			number = -number;
	}

	if (number == 0)
		return (-1);

	return (number);
}

/**
 * process_command - process a given command
 * @p: parameters
 *
 * Return: exit status of the command if found ; error code otherwise
 */
int process_command(parameters_t *p)
{
	pid_t child_pid;
	int code, i = 0;
	struct stat st;
	char copy[2048];

	/* Handling expansion */
	while (p->command[i] != NULL)
	{
		if (p->command[i][0] == '$' && p->command[i][1] == '?')
			sprintf(p->command[i], "%i", p->status);
		else if (p->command[i][0] == '$' && p->command[i][1] == '$')
			sprintf(p->command[i], "%i", getpid());
		else if (p->command[i][0] == '$' && p->command[i][1] != '\0')
			p->command[i] = get_env(&p->command[i][1], p->env, copy);
		i++;
	}

	/* Checking if the command exists */
	if (stat(p->command[0], &st) != 0)
	{
		fprintf(stderr, "%s: 1: %s: not found\n", p->argv[0], p->command[0]);
		return (127);
	}

	child_pid = fork();

	if (child_pid == -1)
	{
		fprintf(stderr, "%s: fork failed\n", p->argv[0]);
		return (-1);
	}

	/* Executing the command */
	else if (child_pid == 0)
		execve(p->command[0], p->command, p->env);
	else
		wait(&code);

	return (WEXITSTATUS(code));
}
