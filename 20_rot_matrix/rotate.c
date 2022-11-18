#include<stdlib.h>

void rotate(char matrix[10][10]) {
    for (int i=0; i < 10; i++) {
        for (int j=0; j < i; j++) {
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = tmp;
        }
    }
    for (int i=0; i < 10; i++) {
        for (int j=0; j < 5; j++) {
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[i][9-j];
            matrix[i][9-j] = tmp;
        }
    }
    return;
}

