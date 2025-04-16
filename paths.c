#include "main.h"

/**
 * _getenv - gets an environment variable
 * @name: name of variable to get
 *
 * Return: value of the environment variable
 */
char *_getenv(const char *name)
{
	extern char **environ;
	int i = 0, cmp = 0;
	char *variable = "";
	char *value = "";
	
	/* Searching for a matching variable */
	while (environ[i] != NULL)
	{
		variable = strtok(environ[i], "=\n");
		value = strtok(NULL, "=\n");

		cmp = strcmp(name, variable);

		if (cmp == 0)
			return (value);

		i++;
	}

	return (NULL);
}

/**
 * create_path_list - creates a singly linked list of all PATH directories
 * @value: value of PATH environment variable
 *
 * Return: head of the list
 */
list_t *create_path_list(char *value)
{
	char *path = "";
	list_t *head = NULL;

	path = strtok(value, ":\n");

	/* Creating a node for each PATH directory */
	while (path != NULL)
	{
		add_node_end(&head, path);
		path = strtok(NULL, ":\n");
	}

	return (head);
}

/**
 * print_list - prints all the elements of a list
 * @head: head of the list
 */
void print_list(const list_t *head)
{
	char *data = "";
	int i = 0;

	/* Printing each element of the list and going to the next one */
	while (head != NULL)
	{
		if (head->str == NULL)
			data = "(nil)";
		else
			data = head->str;

		printf("[Node %i] [%u] %s\n", i, head->len, data);

		head = head->next;
		i++;
	}
}

/**
 * add_node_end - adds a new node at the end of a list
 * @head: head of the list
 * @str: data of the node
 *
 * Return: address of the node
 */
list_t *add_node_end(list_t **head, const char *str)
{
	list_t *new = NULL;
	list_t *current = *head;
	unsigned int i = 0;

	/* Counting length of str */
	while (str[i])
		i++;

	/* Allocating enough memory for the new node */
	new = malloc(i + 1 + sizeof(int) + sizeof(list_t *));

	/* Checking if malloc failed */
	if (new == NULL)
		return (NULL);

	/* Setting node values */
	new->str = strdup(str);
	new->len = i;
	new->next = NULL;

	/* Setting head to new if list is empty */
	if (*head == NULL)
	{
		*head = new;
		return (new);
	}

	/* Reaching the end of the list */
	while (current->next)
		current = current->next;

	/* Adding node at the end of the list */
	current->next = new;
	return (new);
}

/**
 * free_list - frees a list
 * @head: head of the list
 */
void free_list(list_t *head)
{
	list_t *current = head;
	list_t *temp = NULL;

	if (head != NULL)
	{
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
