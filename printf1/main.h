#ifndef MAIN_H
#define MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

#define BUFF_SIZE 1024
#define UNUSED(x)(void)(x)

#define F_HASH 8
#define F_ZERO 4
#define F_MINUS 1
#define F_PLUS 2
#define F_SPACE 16

#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmt - Struct op
 * @fmt: The format.
 * @fn: The function associated.
 */
struct fmt
{
	char fmt;
	int (*fn)(va_list, char[], int, int, int, int);
};


/**
<<<<<<< HEAD
 * typedef struct fmt f_types - Struct op
 *
=======
 * typedef struct fmt f_typ - Struct op
>>>>>>> d4038926e4b588a760b1fbc053274e7324922a08
 * @fmt: The format.
 * @fm_t: The function associated.
 */
typedef struct fmt f_types;

int _printf(const char *format, ...);
void print_buffer(char buffer[], int *buff_ind);
int flag(const char *format, int *i);
int Width(const char *format, int *i, va_list list);
int precisions(const char *format, int *i, va_list list);
int Size(const char *format, int *i);
int handle_print(const char *format, int *i, va_list list, char buffer[],
	int flags, int width, int precision, int size);
int _putchar(char c);

#endif
