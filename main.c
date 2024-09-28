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
		if (argc != 2)
		{
			perror("USAGE: monty file");
			exit(EXIT_FAILURE);
		}
}
