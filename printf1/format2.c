#include "main.h"

/************************* PRINT UNSIGNED NUMBER *************************/
/**
 * print_unsigned - Prints an unsigned decimal number
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed.
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int n = va_arg(types, unsigned long int);
	/*extract the next argument from the va_list types*/
	/*and assign it to the variable n*/

	n = convert_size_unsgnd(n, size);
	/*n = handle different size specifiers and convert*/
	/*the input number to the correct data type*/
	/*based on the size specifier.*/

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	/*add null terminator to the buffer to ensure it contains*/
	/*valid C-str for proper output handling*/

	while (n > 0)
	{	/*converts n into a decimal representation*/
		/*repeatedly extracting digits from the LSB and store as char*/
		buffer[i--] = (n % 10) + '0';
		n /= 10;
	}

	i++;
	/*print output and return no of chars printed*/
	return (write_unsgn(0, i, buffer, flags, width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN OCTAL  ****************/
/**
 * print_octal - Prints an unsigned number in octal notation
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	/*extract the next argument from the va_list types*/
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num; /*creates a copy of num*/

	UNUSED(width);/*unused param casted with a null MACRO*/

	num = convert_size_unsgnd(num, size);
	/*the functn convert_size_unsgnd handles different size*/
	/*specifiers and converts them to work correctly*/

	if (num == 0)
		buffer[i--] = '0'; /*stores 0 in the buffer*/

	buffer[BUFF_SIZE - 1] = '\0'; /*end the array with NULL char*/

	while (num > 0)
	{	/*converts the num to octal representation*/
		/*repeatedly extracting digits from LSB*/
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	/*set the hash flag to signify that it is an octal number*/
	/*adds a prefix 0 if the initial value is not zero*/
	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++; /*move index to correct position in buffer after the loop*/
	/*print the content to the buffer and return the no of chars*/
	return (write_unsgn(0, i, buffer, flags, width, precision, size));
}

/************** PRINT UNSIGNED NUMBER IN HEXADECIMAL **************/
/**
 * print_hexadecimal - Prints an unsigned number in hexadecimal notation
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{	/*calls the print_hexa fn to convert num to hexadecimal*/
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/************* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **************/
/**
 * print_hexa_upper - Prints an unsigned number in upper hexadecimal notation
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Number of chars printed
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/************** PRINT HEX NUM IN LOWER OR UPPER **************/
/**
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @types: Lista of arguments
 * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * Return: Number of chars printed
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width); /*unused param casted with void MACRO*/

	/*handles different size specifiers*/
	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0'; /*stores 0 in the buffer*/

	buffer[BUFF_SIZE - 1] = '\0'; /*end the buffer with \0*/

	while (num > 0)
	{	/*converts the numbers to hexa using the map_to array*/
		/*extracts the last digit from the LSB and the*/
		/*corresponding char from the map_to in stored in the buffer*/
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	/*"hash" flag (F_HASH) is used to adds a prefix '0x' or '0X' to the number.*/
	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		/* flag_ch is the character ('ox' or 'OX') to be used*/
		/*as the prefix when the "hash" flag is set*/
		buffer[i--] = '0';
	}

	i++; /*moves the index back to the correct pos in the buffer after loop*/
	/*prints the content to the buffer and return the no of chars*/
	return (write_unsgn(0, i, buffer, flags, width, precision, size));
}
