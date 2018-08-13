#ifndef _STRING_H
#define _STRING_H 1
 
#include <sys/cdefs.h>
 
#include <stddef.h>
 
#ifdef __cplusplus
extern "C" {
#endif

// Copying
void* memcpy(void* __restrict, const void* __restrict, size_t);
void* memmove(void*, const void*, size_t);
char* strcpy(char* destination, const char* source);
char* strncpy(char* destination, const char* source, size_t num);

// Concatenation
char* strcat(char* destination, const char* source);
char* strncat(char* destination, const char* source, size_t num);

// Comparison
int memcmp(const void*, const void*, size_t);
int strcmp(const char* str1, const char* str2);
int strcoll(const char * str1, const char * str2); // TODO
int strncmp(const char* str1, const char* str2, size_t num);
size_t strxfrm(char * destination, const char * source, size_t num); // TODO

// Searching
void* memchr(void* ptr, int value, size_t num);
char* strchr(char* str, int character);
size_t strcspn(const char* str1, const char* str2);
char* strpbrk(char* str1, const char* str2); // TODO

// Other
void* memset(void*, int, size_t);

size_t strlen(const char*);
 
#ifdef __cplusplus
}
#endif
 
#endif