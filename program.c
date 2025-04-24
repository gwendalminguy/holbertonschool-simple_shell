#include "main.h"

/**
 * start_program - initializes environment and a list of all PATH directories
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
}

/**
 * stop_program - frees everything and exits the program
 * @head: linked list of all PATH directories
 * @line: user input
 * @p: parameters
 */
void stop_program(list_t *head, char *line, parameters_t *p)
{
	int i = 0;

	free(line);
	free_list(head);
	free_env(p->env);

	while (p->history[i] != NULL)
	{
		free(p->history[i]);
		i++;
	}

	exit(p->status);
}
