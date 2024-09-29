#include "monty.h"

/**
* main - an entery for monty interpreter
* @argc: number of arguments
* @argv: arguments
*
* Return: 0 on success
*/
int main(int argc, char *argv[])
{
	int fd, is_push = 0;
	char *buffer, *token;
	unsigned int line = 1;
	stack_t *h = NULL;
	ssize_t n_read;

	if (argc != 2)
	{
		printf("USAGE: monty file");
		exit(EXIT_FAILURE);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	buffer = malloc(sizeof(char) * 10000);
	if (buffer == NULL)
		return (0);
	n_read = read(fd, buffer, 10000);
	if(n_read == -1)
	{
		free(buffer);
		close(fd);
		exit(EXIT_FAILURE);
	}
	token = strtok(buffer, "\n\t\a\r ;:");
	while (token != NULL)
	{
		if (is_push == 1)
		{
			push(&h, line, token);
			is_push = 0;
			strtok(NULL, "\n\t\a\r ;:");
			line++;
			continue;
		}
		else if (strcmp(token, "push") == 0)
		{
			is_push = 1;
			token = strtok(NULL, "\n\t\a\r ;:");
			continue;
		}
		else
		{
			if (select_func(token) != 0)
			{
				select_func(token)(&h, line);
			}
			else
			{
				free_dlist(&h);
				printf("L%d: unknown instruction %s\n", line, token);
				exit(EXIT_FAILURE);
			}
		}
		line++;
		token = strtok(NULL, "\n\t\a\r ;:");
	}
	free_dlist(&h); free(buffer);
	close(fd);
	return (0);

}
