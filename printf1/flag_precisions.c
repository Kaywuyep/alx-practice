#include "main.h"

/**
 * flag - Calculates active flags from the format string
 * @format: Formatted string in which to find the flags
 * @i: Pointer to the index in the format string
 * Return: Flags calculated based on the encountered flag characters
 */
int flag(const char *format, int *i)
{
	int j, curr_i;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	/* Start from the next character of the current index */
	for (curr_i = *i + 1; format[curr_i] != '\0'; curr_i++)
	{
		/* Check each flag character till it gets to the end of fmt str '\0' */
		for (j = 0; FLAGS_CH[j] != '\0'; j++)
		{
			/* If a flag character is found, set the corresponding bit */
			if (format[curr_i] == FLAGS_CH[j])/*this means a flag has been found*/
			{
				flags |= FLAGS_ARR[j];/*value of flags is added to FLAGS-ARR*/
				/*it sets the appropriate flag bit to 1, indicating the flag is active.*/
				break;
			}
		}

		/* If no flag character is found, break the loop */
		if (FLAGS_CH[j] == 0)
			break;
	}

	/* Decrement the current index by 1 and update the pointer */
	/*allows the calling function to continue processing the fmt str*/
	*i = curr_i - 1;

	/* Return the calculated flags */
	return (flags);
}

/**
 * precisions - Calculates the precision value used for printing
 * @format: Formatted string in which to find the precision value
 * @i: Pointer to the index in the format string
 * @list: Variable argument list containing the additional arguments
 * Return: Precision value as an integer
 */
int precisions(const char *format, int *i, va_list list)
{
	int curr_i = *i + 1;
	int precision = -1; /*Default precision if not specified*/

	/* Check if the format string contains a dot (.) for precision */
	if (format[curr_i] != '.')
		return (precision); /*Return the default precision*/

	precision = 0; /*Reset precision to 0 for explicit precision specification*/

	/* Loop through the format string to extract the precision value */
	for (curr_i += 1; format[curr_i] != '\0'; curr_i++)
	{
		/* If the character is a digit, update the precision value */
		if (is_digit(format[curr_i]))
		{
			precision *= 10;
			precision += format[curr_i] - '0';
		}
		/* If the character is '*', get the precision*/
		/*from the variable argument list */
		else if (format[curr_i] == '*')
		{
			curr_i++;
			precision = va_arg(list, int);
			break;
		}
		else
			break; /*Stop if a non-digit and non-'*' character is encountered*/
	}

	/* Decrement the current index by 1 and update the pointer */
	*i = curr_i - 1;

	/* Return the extracted precision value */
	return (precision);
}
