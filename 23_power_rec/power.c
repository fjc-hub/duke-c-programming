#include<stdlib.h>

unsigned power(unsigned x, unsigned y) {
    if (y == 0) {
        return 1;
    }
    if (x == 0) {
        return 0;
    }
    if (y == 1) {
        return x;
    }
    unsigned tmp = power(x, y / 2);
    if (y % 2 == 1) {
        return x * tmp * tmp;
    } else {
        return tmp * tmp;
    }
}