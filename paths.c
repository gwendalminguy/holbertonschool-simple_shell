#include "main.h"

/**
 * create_path_list - creates a singly linked list of all PATH directories
 * @env: environment variables
 *
 * Return: head of the list
 */
list_t *create_path_list(char **env)
{
	char *path = NULL;
	char *value = NULL;
	list_t *head = NULL;

	value = get_env("PATH", env);

	if (value == NULL)
		return (NULL);

	path = strtok(value, ":\n");

	/* Creating a node for each PATH directory */
	while (path != NULL)
	{
		add_node_list(&head, path);
		path = strtok(NULL, ":\n");
	}

	free(value);

	return (head);
}

/**
 * search_path_list - searches for a given command in all PATH directories
 * @command: command to search
 * @paths: linked list of all PATH directories
 *
 * Return: full command path
 */
char *search_path_list(char *command, list_t *paths)
{
	struct stat st;
	char full_path[1024];
	list_t *current = paths;
	int size = 0;

	/* Searching for the command in each PATH */
	while (current != NULL)
	{
		memset(full_path, 0, sizeof(full_path));

		sprintf(full_path, "%s/%s", current->str, command);

		if (stat(full_path, &st) == 0)
		{
			sprintf(command, "%s", full_path);
			return (command);
		}

		current = current->next;
	}

	return (command);
}

/**
 * print_list - prints all the elements of a linked list
 * @head: head of the list
 */
void print_list(const list_t *head)
{
	char *data = NULL;
	unsigned int i = 0;

	/* Printing each element of the list and going to the next one */
	while (head != NULL)
	{
		if (head->str == NULL)
			data = "(nil)";
		else
			data = head->str;

		printf("[Node %u] [%u] %s\n", i, head->len, data);

		head = head->next;
		i++;
	}
}

/**
 * add_node_list - adds a new node at the end of a linked list
 * @head: head of the list
 * @str: data of the node
 */
void add_node_list(list_t **head, const char *str)
{
	list_t *new = NULL;
	list_t *current = *head;
	unsigned int i = 0;

	/* Counting length of str */
	while (str[i])
		i++;

	/* Allocating enough memory for the new node */
	new = malloc(i + sizeof(list_t));

	/* Checking if malloc failed */
	if (new != NULL)
	{
		/* Setting node values */
		new->str = strdup(str);
		new->len = i;
		new->next = NULL;

		/* Setting head to new if list is empty */
		if (*head == NULL)
		{
			*head = new;
			return;
		}

		/* Reaching the end of the list */
		while (current->next)
			current = current->next;

		/* Adding node at the end of the list */
		current->next = new;
	}
}

/**
 * free_list - frees a linked list
 * @head: head of the list
 */
void free_list(list_t *head)
{
	list_t *current = NULL;
	list_t *temp = NULL;

	if (head != NULL)
	{
		current = head;

		while (current)
		{
			/* Saving address of next element */
			temp = current->next;

			/* Freeing current element */
			if (current->str)
				free(current->str);

			free(current);

			/* Switching current element to next one */
			current = temp;
		}
	}
}
