#include <string.h>
#include <stdio.h>
 
char* strncat(char* destination, const char* source, size_t num) {

    size_t i = 0;
    size_t len = strlen(destination);
    while(source[i] && i < num) {
        destination[len + i] = source[i];
        i++;
    }
    destination[len + i] = '\0';

    return destination;
}

char* strcat(char* destination, const char* source) {    
    return strncat(destination, source, strlen(source));
}

int strncmp(const char * str1, const char * str2, size_t num) {

    int dif = 0;
    size_t i = 0;
    while((str1[i] || str2[i]) && i < num && (dif == 0)) {
        dif = str1[i] - str2[i];
        i++;
    }

    return dif;
}

int strcmp(const char * str1, const char * str2) {  
    return strncmp(str1, str2, strlen(str1));
}

int strcoll(const char * str1, const char * str2) {
    // TODO clocal transformation
    return strcmp(str1, str2);
}

size_t strxfrm(char * destination, const char * source, size_t num) {
    // TODO clocal transformation of source

    if (destination != NULL && num != 0) {
        strncpy(destination, source, num);
    }
    return strlen(destination);
}

char* strchr(char * str, int character) {
    return (char*) memchr(str, character, strlen(str));
}

size_t strcspn(const char* str1, const char* str2) {

    // TODO Test
    int i = 0;
    while (str1[i]) {
        for (size_t k = 0; k < strlen(str2); k++) {
            if (str1[i] == str1[k]) {
                return (size_t) i+1;
            }
        }
        i++;
    }

    return strlen(str1);
}

char* strpbrk(char* str1, const char* str2) {

    size_t i = 0;
    while (*(str1 + i) != '\0') {
        
        size_t j = 0;
        while (j < strlen(str2)) {
            if (*(str1 + i) == *(str2 + j)) {
                return (str1 + i);
            }
            j++;
        }

        i++;
    }
    
    return NULL;
}

char* strncpy(char * destination, const char * source, size_t num) {

    size_t i = 0;
    while(i < num) {

        if (i < strlen(source)) {
            destination[i] = source[i];
        } else {
            destination[i] = '\0';
        }
        i++;
    }

    return destination;
}

char* strcpy(char * destination, const char * source) {
    return (char*) memcpy((void*) destination, (void*) source, strlen(source)+1);
}

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}