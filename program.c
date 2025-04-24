#include "main.h"

/**
 * start_program - initializes environment and a PATH list
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
 * stop_program - frees everything and export history
 * @line: user input
 * @head: linked list of all PATH directories
 * @env: environùent variables
 * @history: history of commands
 */
void stop_program(char *line, list_t *head, char **env, char **history)
{
	int i = 0;

	free(line);
	free_list(head);
	free_env(env);

	while (history[i] != NULL)
	{
		free(history[i]);
		i++;
	}
}
