#include <limits.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#if defined(__is_libk)
#include <kernel/tty.h>
#endif

#define STD_COLOR 7
#define DBG_COLOR 4

static bool print(const char* data, size_t length)
{
	const unsigned char* bytes = (const unsigned char*) data;
	for (size_t i = 0; i < length; i++) {
		if (putchar(bytes[i]) == EOF) {
			return false;
		}
	}
	return true;
}

static int print_VA(const char* restrict format, va_list parameters)
{
	int written = 0;
 
	while (*format != '\0') {
		size_t maxrem = INT_MAX - written;
 
		if (format[0] != '%' || format[1] == '%') {
			
			if (format[0] == '%') {
				format++;
			}

			size_t amount = 1;
			while (format[amount] && format[amount] != '%') {
				amount++;
			}
			
			if (maxrem < amount) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			
			if (!print(format, amount)) {
				return -1;
			}

			format += amount;
			written += amount;
			continue;
		}
 
		const char* format_begun_at = format++;
 
		if (*format == 'c') {
			format++;
			char c = (char) va_arg(parameters, int /* char promotes to int */);
			if (!maxrem) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(&c, sizeof(c)))
				return -1;
			written++;
		}
		else if (*format == 's')
		{
			format++;
			const char* str = va_arg(parameters, const char*);
			size_t len = strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		} 
		else if (*format == 'd' ||
				 *format == 'i' || 
				 *format == 'u' || 
				 *format == 'o' ||
				 *format == 'x' || *format == 'X' ||
				 *format == 'p') 
		{
			char buffer[sizeof(int)*8+1];
			char* str = &buffer[0];

			if (*format == 'd' || *format == 'i') {
				int i = va_arg(parameters, int);
				itoa(i, str, 10);
			} else if (*format == 'u') {
				unsigned int i = va_arg(parameters, unsigned int);
				uitoa(i, str, 10);
			} else if (*format == 'o') {
				unsigned int i = va_arg(parameters, unsigned int);
				uitoa(i, str, 8);
			} else if (*format == 'x' || *format == 'X') {
				unsigned int x = va_arg(parameters, unsigned int);
				uitoa(x, str, 16);
			} else if (*format == 'p') {
				void* x = va_arg(parameters, void*);
				uitoa((uint32_t) x, str, 10);
			}

			format++;
			size_t len = strlen(str);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(str, len))
				return -1;
			written += len;
		}
		else 
		{
			format = format_begun_at;
			size_t len = strlen(format);
			if (maxrem < len) {
				// TODO: Set errno to EOVERFLOW.
				return -1;
			}
			if (!print(format, len)) {
				return -1;
			}
			written += len;
			format += len;
		}
	}

	return written;
}

// Print formatted output
int printf(const char* restrict format, ...)
{
	terminal_setcolor(STD_COLOR);

	va_list parameters;
	va_start(parameters, format);
	int written = print_VA(format, parameters);
	va_end(parameters);
	
	return written;
}

// Print Debug output in different color
int dprintf(const char* restrict format, ...)
{
	terminal_setcolor(DBG_COLOR);
	
	va_list parameters;
	va_start(parameters, format);
	int written = print_VA(format, parameters);
	va_end(parameters);

	return written;
}