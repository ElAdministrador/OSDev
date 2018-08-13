#include <stddef.h>
#include <stdlib.h>

int abs(int x) {
    if (x < 0) {
        return -1 * x;
    } else {
        return x;
    }
}