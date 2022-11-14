#include<stdlib.h>

size_t maxSeq(int * array, size_t n) {
    size_t ans = 0;
    if (array == NULL) {
        return ans;
    }
    int maxL = 0;
    for (int i=0; i < n; i++) {
        if (i == 0 || array[i-1] < array[i]) {
            maxL++;
        } else {
            maxL = 1;
        }
        if (maxL > ans) {
            ans = maxL;
        }
    }
    return ans;
}
