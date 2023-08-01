#include "main.h"
/************************* PRINT CHAR *************************/
/**
 * print_char - Prints a char
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: Width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_char(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	/*extract the char and promotes it to an int*/
	char c = va_arg(types, int);
	/*passes the character to the handle_write fn*/
	return (handle_write_char(c, buffer, flags, width, precision, size));
}
/************************* PRINT A STRING *************************/
/**
 * print_string - Prints a string
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	/*extract the passed string from the va_arg*/
	char *str = va_arg(types, char *);
	/*casts the flag, buffer and size params to void*/
	UNUSED(flags);
	UNUSED(buffer);
	UNUSED(size);
	if (str == NULL)/*handle NULL pointer*/
	{	/*sets str to point to the string (null)*/
		str = "(null)";
		if (precision >= 6)
			str = "      ";/*padding with spaces*/
	}
	/*calculate length of string*/
	while (str[length] != '\0')
		length++;
	/*handle cases with specified precision*/
	if (precision >= 0 && precision < length)
		length = precision;
	else if (precision == 0)/*for "%.0s" and "%.*s"case*/
		length = 0;

	if (width > length)/*handle width padding*/
	{
		if (flags & F_MINUS)/*handle string left alignment*/
		{	/*prints string first before padding*/
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else /*if flag is not active*/
		{	/*prints padding spaces first before str*/
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	} /*no width padding needed, print string normally*/
	return (write(1, str, length));
}
/************************* PRINT PERCENT SIGN *************************/
/**
 * print_percent - Prints a percent sign
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_percent(va_list types, char buffer[],
int flags, int width, int precision, int size)
{
	/*casts the unused params using the void MACRO*/
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	/*prints the % character*/
	return (write(1, "%%", 1));
}
/************************* PRINT INT *************************/
/**
 * print_int - Print int
 * @types: List of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_int(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	/*init i to index of second-to-last element in buffer*/
	int i = BUFF_SIZE - 2;
	int is_negative = 0; /*to determine negative numbers*/
	/*extracts the number from va_arg*/
	long int n = va_arg(types, long int);
	unsigned long int num;
	/*converts the number based on the size specifier*/
	n = convert_size_number(n, size);
	/*stores 0 to buffer based on result of convert_size fn*/
	if (n == 0)
		buffer[i--] = '0';
	/*set the last element of the buffer to NULL-character*/
	buffer[BUFF_SIZE - 1] = '\0';
	/*casts the n variable to and update num to handle - */
	num = (unsigned long int)n;
	/*checks if n is negative*/
	if (n < 0)
	{	/*gets the absolute value of n*/
		num = (unsigned long int)((-1) * n);
		is_negative = 1; /*indicates number is negative*/
	}
	/*recursively adds the num into the buffer till num == 0*/
	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}
	i++;
	/*writes number to the standard output*/
	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}
/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
int flags, int width, int precision, int size)
{	/*n to be printed in binary format*/
	/*m to used as a mask to extract each bit on n*/
	unsigned int n, m, i, sum; /*i and sum used in the loop*/
	unsigned int a[32]; /*array to store binary digits*/
	int count;
	/*unused params casted with void MACRO*/
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	n = va_arg(types, unsigned int); /*extracts the num*/
	m = 2147483648; /*mask to extract each bit 2^31*/

	a[0] = n / m; /*first arr element holds MSB of n*/
	/*loop to fill the rest of binary digits*/
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2; /*stores remainder result*/
	}
	/*writes the binary representation of n to the std output*/
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{	/*checks if sum of prev bits and current is non-zero*/
		/*or loops reaches the end of last bit*/
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i]; /*adds the ASCII value*/

			write(1, &z, 1); /*prints binary digit to std output*/
			count++; /*counts characters written*/
		}
	}
	return (count); /*return the total no of chars written*/
}
