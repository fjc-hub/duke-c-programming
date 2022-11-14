#include<stdlib.h>
#include<stdio.h>

size_t maxSeq(int * array, size_t n);

int main(void) {
    // case 0
    if (maxSeq(NULL, 0) != 0 ) {
        return EXIT_FAILURE;
    }
    // case 1
    size_t x1 = 10;
    int arr1[] = {1, 2, 1, 3, 5, 7, 2, 4, 6, 9};
    if (maxSeq(arr1, x1) != 4) {
        return EXIT_FAILURE;
    }
    // case 2
    size_t x2 = 3;
    int arr2[] = {1,2,3};
    if (maxSeq(arr2, x2) != 3) {
        return EXIT_FAILURE;
    }
    // case 3
    size_t x3 = 12;
    int arr3[] = {1,2,3,4,5,5,6,7,8,9,10,11};
    if (maxSeq(arr3, x3) != 7) {
        return EXIT_FAILURE;
    }
    // case 4
    size_t x4 = 8;
    int arr4[] = {1,2,3,4,5,1,2,3};
    if (maxSeq(arr4, x4) != 5) {
        return EXIT_FAILURE;
    }
    // case 5
    size_t x5 = 5;
    int arr5[] = {2, -3, 5, 6, 8};
    if (maxSeq(arr5, x5) != 4) {
        return EXIT_FAILURE;
    }
    // case 6
    size_t x6 = 4;
    int arr6[] = {5,4,3,2};
    if (maxSeq(arr6, x6) != 1) {
        return EXIT_FAILURE;
    }
    // case 7
    size_t x7 = 4;
    int arr7[] = {-3,-2,0,-10};
    if (maxSeq(arr7, x7) != 3) {
        return EXIT_FAILURE;
    }
    // case 8
    size_t x8 = 11;
    int arr8[] = {1,2,3,4,3,2,3,4,5,6,0};
    if (maxSeq(arr8, x8) != 5) {
        return EXIT_FAILURE;
    }
    // case 9
    
    return EXIT_SUCCESS;
}
