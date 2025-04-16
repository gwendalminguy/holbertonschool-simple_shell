#include "main.h"

void get_arguments(char *line, char **arguments);

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

		printf("%s\n", arguments[0]);

		free(line);
	}
}

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
