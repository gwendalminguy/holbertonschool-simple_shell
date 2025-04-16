#include "main.h"

/**
 * main - ...
 *
 * Return: 0
 */
int main(void)
{
	char *line;
	size_t len;
	ssize_t read;
	char *arguments[4096];

	while (1)
	{
		printf("$ ");
		
		read = getline(&line, &len, stdin);

		if (read < 0)
		{
			dprintf(STDERR_FILENO, "Error\n");
			break;
		}

		get_arguments(line, arguments);

		free(line);
	}
}

/**
 * get_arguments - transforms user input in an array of strings
 * @line: user input
 * @arguments: array of strings
 */
void get_arguments(char *line, char **arguments)
{
	int i = 0;
	char *str;

	str = strtok(line, " \n");

	while (str != NULL)
	{
		arguments[i] = str;
		str = strtok(NULL, " \n");
		i++;
	}
}
