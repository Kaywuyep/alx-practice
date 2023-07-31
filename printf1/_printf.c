#include "main.h"

/**
 * _printf - Printf function
 * @format: format string containing optional format specifiers.
 *
 * Return: The number of characters printed
 */
int _printf(const char *format, ...)
{
	int i, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;

	va_list list;/*the first argument in the format string*/

	char buffer[BUFF_SIZE];

	if (format == NULL)/*check if format pointer is pointing to NULL*/
		return (-1);/*if so return error*/
	va_start(list, format);/*initialize the list variable to handle args passed*/
	for (i = 0; format && format[i] != '\0'; i++)/*loop through the string*/
	{
		if (format[i] != '%')/*checks if the format is a regular char to be printed*/
		{
			buffer[buff_ind++] = format[i];/*regular char is copied to buffer array*/
				if (buff_ind == BUFF_SIZE)/*checks if buffer has reached maximum space*/
					print_buffer(buffer, &buff_ind);/*prints content of buffer to console*/
				printed_chars++;
		}
		else /*format[i] == '%', the format to be printd is irregular or non custom*/
		{
			print_buffer(buffer, &buff_ind);/*clear the buffer first*/
			/*process the format specifies to be encounterd*/
			flags = flag(format, &i);/*retrieve any flag specified eg. '+', '-'*/
				width = Width(format, &i, list);/*handles field width specified eg."%10d"*/
				precision = precisions(format, &i, list);/*handles precisn specifd "%.3f"*/
				size = Size(format, &i);/*specifier to modify any data size to be prnted*/
				++i;
				/*handle the printing of formatted data specified*/
				printed = handle_print(format, &i, list, buffer, flags,
						width, precision, size);
				if (printed < 1)/*check if there is any error was encountered*/
					return (-1);/*if an err was encounted return*/
				printed_chars += printed;/*update number of chars printed*/
		}
	}
	print_buffer(buffer, &buff_ind);/*print contents and reset to zero*/
	va_end(list);/*clean up the buffer*/

	return (printed_chars);
}

/**
 * print_buffer - a function that prints content of a buffer
 * @buffer: char variable
 * @buff_ind: shows current position of the buffer index
 */
void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)/*checks if buffer is not empty*/
		write(1, &buffer[0], *buff_ind);/*print the content of the buffer*/

	*buff_ind = 0;/*reset the buffer index to 0 for reuse*/
}
