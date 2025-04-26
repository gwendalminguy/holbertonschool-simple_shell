#include "main.h"

/**
 * start_program - starts the program
 *
 * Description: initializes variables
 *		copies environment variables
 *		creates a list of all PATH directories
 *		reads and loads history of commands
 *
 * @head: head of the list
 * @argv: arguments of the program
 * @env: environment variables
 * @p: parameters
 */
void start_program(list_t **head, char **argv, char **env, parameters_t *p)
{
	p->status = 0;
	p->argv = argv;

	memset(p->env, 0, sizeof(p->env));
	memset(p->history, 0, sizeof(p->history));

	copy_env(env, p->env);
	*head = create_path_list(env);
	load_history(env, p);
}

/**
 * stop_program - stops the program
 *
 * Description: frees everything
 *		exports history of commands (upcoming)
 *		exits the program with status
 *
 * @head: linked list of all PATH directories
 * @line: user input
 * @p: parameters
 */
void stop_program(list_t **head, char *line, parameters_t *p)
{
	export_history(p->env, p);

	free(line);
	free_list(*head);
	free_array(p->env);
	free_array(p->history);

	exit(p->status);
}

/**
 * load_history - loads the history of commands
 * @env: environment variables
 * @p: parameters
 */
void load_history(char **env, parameters_t *p)
{
	char home[1024] = {0}, buffer[4096] = {0};
	char *line = NULL, *path = NULL;
	char *file = ".simple_shell_history";
	ssize_t bytes_read = 0;
	struct stat st;
	int size = 0, i = 0, fd;

	get_env("HOME", env, home);

	if (home[0] != '\0')
	{
		size = 2 + strlen(home) + strlen(file);
		path = malloc(size);

		if (path != NULL)
		{
			sprintf(path, "%s/%s", home, file);

			if (stat(path, &st) == 0)
			{
				fd = open(path, O_RDONLY, 400);
				bytes_read = read(fd, buffer, 4096);
				while (bytes_read > 0)
				{
					line = strtok(buffer, "\n");
					while (line != NULL)
					{
						p->history[i] = malloc(2 + strlen(line));
						sprintf(p->history[i], "%s\n", line);
						line = strtok(NULL, "\n");

						i++;

						/* Handling modulo 4096 */
						if (i == 4096)
						{
							free_array(p->history);
							memset(p->history, 0, sizeof(p->history));
							i = 0;
						}
					}
					bytes_read = read(fd, buffer, 4096);

					if (bytes_read == -1)
					{
						fprintf(stderr, "%s: history: read failure\n", p->argv[0]);
						p->status = -1
						break;
					}
				}
				close(fd);
			}
			free(path);
		}
	}
	p->position = i;
}

/**
 * export_history - exports the history of commands
 * @env: environment variables
 * @p: parameters
 */
void export_history(char **env, parameters_t *p)
{
	char home[1024] = {0};
	char *path = NULL;
	char *file = ".simple_shell_history";
	ssize_t bytes_written = 0;
	int size = 0, i = p->position, fd, length = 0;

	get_env("HOME", env, home);

	if (home[0] != '\0')
	{
		size = 2 + strlen(home) + strlen(file);
		path = malloc(size);

		if (path != NULL)
		{
			sprintf(path, "%s/%s", home, file);
			fd = open(path, O_WRONLY | O_APPEND | O_CREAT, 0600);

			while (i < 4096 && p->history[i] != NULL)
			{
				length = strlen(p->history[i]);
				bytes_written = write(fd, p->history[i], length);
				if (bytes_written == -1)
				{
					fprintf(stderr, "%s: history: write failure\n", p->argv[0]);
					p->status = -1;
					break;
				}
				i++;
			}
			close(fd);
			free(path);
		}
	}
	p->position = 0;
}
