#include "main.h"
/**
 * _putchar - print char to stdout
 * @c
 * Return: 1 success
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
