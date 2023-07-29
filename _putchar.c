#include <unistd.h>
/**
 * _putchar - a function that prints to stdout
 * @c: character to print
 * Return: 1
 */
int _putchar(char c)
{
return (write(1, &c, 1));
}
