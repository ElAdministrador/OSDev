#include <stddef.h>
#include <stdlib.h>
#include <math.h>

char * itoa(int value, char * str, int base) {
    
    int i = 0;
    _Bool neg = value < 0;

    if (value == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    while(value != 0) {
        char c = (char) abs(value % base) + '0';
        str[i++] = c;
        value = value / base;
    }

    if (neg) {
        str[i++] = '-';
    }

    size_t len = i;
    int imid = i/2;
    if (len % 2 == 1) {
        imid++;
    }
    // rotate string buffer
    for(int j = 0; j < imid; j++) {
        i = len-j-1;
        char tmp = str[j];
        str[j] = str[i];
        str[i] = tmp;
    }
    str[len] = 0;

    return str;
}

// Convert unsigned number to string
// Base 16 converts to Hex
char * uitoa(unsigned int value, char * str, int base) {

    int i = 0;

    if (value == 0) {
        str[i++] = '0';
    }

    while(value != 0) {
        char c = '\0';
        if (abs(value % base) < 10) {
            c = (char) abs(value % base) + '0';
        } else {
            for (int x = 10; x < 16; x++) {
                if (abs(value % base) == x && base == 16) {
                    c = (char) ('A' + x - 10);
                }
            }
        }
        str[i++] = c;
        value = value / base;
    }

    size_t len = i;
    int imid = i/2;
    if (len % 2 == 1) {
        imid++;
    }
    // rotate string buffer
    for(int j = 0; j < imid; j++) {
        i = len-j-1;
        char tmp = str[j];
        str[j] = str[i];
        str[i] = tmp;
    }
    str[len] = 0;

    return str;
}