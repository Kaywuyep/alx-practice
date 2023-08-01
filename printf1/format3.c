#include "main.h"

/****************** PRINT POINTER ******************/
/**
 * print_pointer - Prints the value of a pointer variable
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	/*unused params casted with void MACRO*/
	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL) /*checks if pointer addr is NULL*/
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision); /*unused params*/

	/*casts the pointer to unsigned long*/
	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{	/*converts the pointer's value to it's hexadecimal rep*/
		/*stores it in the buffer array using the map_to array*/
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}
	/*pad charater with 0 is F_ZERO is set & F_MINUS is not set*/
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	/*adds extra character to the output if F_PLUS is set*/
	if (flags & F_PLUS)
		extra_c = '+', length++;
	/*adds a space character if F_SPACE is set*/
	else if (flags & F_SPACE)
		extra_c = ' ', length++;
	ind++; /*returns the index to the correct position after loop*/
	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/************************* PRINT NON PRINTABLE *************************/
/**
 * print_non_printable - Prints ascii codes in hexa of non printable chars
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	/*i - used to iterate the string*/
	/*offset - used to track of additional chars added to buffer*/
	/*due to non-printable characters*/
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	/*unused params casted with a void MACRO*/
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL) /*if string is NULL*/
		return (write(1, "(null)", 6)); /*print null*/

	while (str[i] != '\0') /*loop through the string*/
	{	/*checks if the char is printable or not using the fn*/
		if (is_printable(str[i]))
			buffer[i + offset] = str[i]; /*copies char to buffer*/
		else /*update the offset to account for non-printable chars*/
			offset += append_hexa_code(str[i], buffer, i + offset);

		i++;
	}
	/*end the buffer with NULL character*/
	buffer[i + offset] = '\0';
	/*write entire buffer to the std output and returns of char written*/
	return (write(1, buffer, i + offset));
}

/************************* PRINT REVERSE *************************/
/**
 * print_reverse - Prints reverse string.
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	/*unused params casted with a void MACRO*/
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	/*extracts string from va_list*/
	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);
		/*Assigns Null to the string*/
		str = ")Null(";
	}
	/*calculate the length of the string*/
	for (i = 0; str[i]; i++)
		;
	/*print characters in reverse order*/
	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];
		/*retrieves char at the current index and writes to std output*/
		write(1, &z, 1);
		count++; /*keeps track of no of chars printed*/
	}
	return (count); /*returns no of chars*/
}
/************************* PRINT A STRING IN ROT13 *************************/
/**
 * print_rot13string - Print a string in rot13.
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of chars printed
 */
int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x; /*temp variable to store characters during processing*/
	char *str;
	unsigned int i, j; /*loop indexes used for iteration*/
	int count = 0;
	/*both arrays to represent the mappings for ROT13 encoding*/
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	/*unused params casted with void MACRO*/
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL) /*checks if string is null*/
		str = "(AHYY)";
	for (i = 0; str[i]; i++) /*loop through the string*/
	{
		for (j = 0; in[j]; j++) /*loop through the in array*/
		{
			if (in[j] == str[i]) /*compares if there's a match*/
			{
				x = out[j]; /*stores the match*/
				write(1, &x, 1); /*prints the char*/
				count++; /*increment count of printed chars*/
				break; /*sends control back to the loop*/
			}
		}
		if (!in[j]) /*if match is not found in the in array*/
		{
			x = str[i]; /*captures the real char*/
			write(1, &x, 1); /*prints the char*/
			count++; /*increment count of printed chars*/
		}
	}
	return (count); /*returns total no of chars printed*/
}
