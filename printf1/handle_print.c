#include "main.h"
/**
 * handle_print - Prints an argument based on its type
 * @format: Formatted string in which to print the arguments
 * @list: Variable argument list containing the additional arguments
 * @i: Index in the format string to process
 * @buffer: Buffer array to handle print
 * @flags: Active flags for formatting
 * @width: Width specifier for formatting
 * @precision: Precision specifier for formatting
 * @size: Size specifier for formatting
 * Return: Number of characters printed or -1 if an unknown specifier is found
 */
int handle_print(const char *format, va_list list, int i, char buffer[],
		int flags, int width, int precision, int size)
{
	int j, unknow_len = 0, printed_chars = -1;
	f_typ f_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};/*struct for handling fmt specifiers and printn funct*/
	for (j = 0; f_types[j].fmt != '\0'; j++)/*loop through for matchin fmt speci*/
	{/* Check if the current character in the fmt str matches any specifier*/
		if (format[i] == f_types[j].fmt)
		{/* Call the printing funct for the specifier and get num of printed char*/
			printed_chars = f_types[j].fn(list, buffer, flags, width, precision, size);
			break; /*Exit the loop as the specifier is found*/
		}
	}
	if (f_types[j].fmt == '\0')/*if specifr is not found(unkwown specifier*/
		/* Print the unknown specifier as is */
		if (format[i] == '\0')
		{
			unknow_len += _putchar('%'); /*Print the '%' character*/
			unknow_len += _putchar('\0'); /*Print the null char at the end of fmt str*/
		}
		else
		{/* Print any preceding flags or width char before the unknown specifier */
			if (format[i - 1] == ' ')
				unknow_len += _putchar(' '); /*Print a space character*/
			else if (width)
			{
				i--; /*Move the index one step back to handle width*/
				while (format[i] != ' ' && format[i] != '%')/*move ind  bk til % is found*/
					i--;
				if (format[i] == ' ')
					i--; /*Move one step back if the character is a space*/
				return (1); /*Return 1 to indicate processing the width*/
			}
			unknow_len += _putchar(format[i]); /* Print the unknown specifier char*/
		}
		return (unknow_len); /*the num of char printd for the unknown specifier*/
		return (printed_chars); /*Return the num of char for the known specifier*/
}
