#include "main.h"

/**
 * Width - Calculates the width value used for printing
 * @format: Formatted string in which to find the width value
 * @i: Pointer to the index in the format string
 * @list: Variable argument list containing the additional arguments
 *
 * Return: Width value as an integer
 */
int Width(const char *format, int *i, va_list list)
{
	int curr_i;
	int width = 0; /*Default width if not specified*/

	/* Loop through the format string to extract the width value */
	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		/* If the character is a digit, update the width value */
		if (is_digit(format[curr_i]))
		{
			width *= 10;
			width += format[curr_i] - '0';
		}
		/* If the character is '*', get the width from the variable argument list */
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break; /*Stop if a non-digit and non-'*' character is encountered*/
	}

	/* Decrement the current index by 1 and update the pointer */
	*i = curr_i - 1;

	/* Return the extracted width value */
	return (width);
}

/**
 * Size - Calculates the size specifier used for formatting output
 * @format: Formatted string in which to find the size specifier
 * @i: Pointer to the index in the format string
 *
 * Return: Size specifier value as an integer
 */
int Size(const char *format, int *i)
{
	int curr_i = *i + 1;
	int size = 0; /*Default size if not specified*/

	/* Check for 'l' (long) size specifier */
	if (format[curr_i] == 'l')
		size = S_LONG;
	/* Check for 'h' (short) size specifier */
	else if (format[curr_i] == 'h')
		size = S_SHORT;

	/* Update the current index based on the found size specifier */
	if (size == 0)
		*i = curr_i - 1;
	else
		*i = curr_i;

	/* Return the calculated size specifier value */
	return (size);
}
