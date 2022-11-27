#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

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



int main(int argc, char ** argv) {
    if (argc != 2) {
        fprintf(stderr, "argument number error\n");
        return EXIT_FAILURE;
    }
    FILE * in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "open file(%s) error\n", argv[1]);
        return EXIT_FAILURE;
    }
    char * p0 = strstr(argv[1], ".txt");
    const char suffix[4] = {'.', 'o', 'u', 't'};
    for (int i = 0; (*p0) != '\0' && i < 4; i++) {
        *p0 = suffix[i];
        p0++;
    }
    FILE * out = fopen(argv[1], "w+");
    if (out == NULL) {
        fprintf(stderr, "open file(%s) error\n", argv[1]);
        return EXIT_FAILURE;
    }
    // read in and initialize matrix
    char matrix[10][10];
    int x = 0, y = 0, ch = 0, row = 0;
    while ((ch = fgetc(in)) != EOF) {
        if (ch == -1 && errno < 0) {
            fprintf(stderr, "system call fail in fgetc(in) library call\n");
            return EXIT_FAILURE;
        }
        row++;
        int i = 0;
        if (ch == '\n') {
            fprintf(stderr,"short-line\n");
            return EXIT_FAILURE;
        }
        do {
            matrix[x][y] = ch;
            y++;
            if (y == 10) {
                x++;
                y = 0;
            }
            // next
            i++;
            if ((ch = fgetc(in)) == '\n') {
                if (i != 10) {
                    fprintf(stderr,"short-line\n");
                    return EXIT_FAILURE;
                }
            }
        } while (i < 10);
        if (ch != '\n') {
            fprintf(stderr,"long-line\n");
            return EXIT_FAILURE;
        }
    }
    if (row != 10) {
        fprintf(stderr, "row number error: %d\n", row);
        return EXIT_FAILURE;
    }
    // rotate
    rotate(matrix);
    // write out
    // for (int i = 0; i < 10; i++) {
    //     char buffer[11];
    //     for (int j = 0; j < 10; j++) {
    //         buffer[j] = matrix[i][j];
    //     }
    //     buffer[10] = '\n';
    //     if (fputs(buffer, out) == EOF) {  // The fputs() function returns EOF if an error occurs
    //         fprintf(stderr, "fputs fail\n");
    //         return EXIT_FAILURE;
    //     }
    // }
    for (int x=0;x<10;x++){
        for (int y=0;y<10;y++){
	        printf("%c",matrix[x][y]);
        }
        printf("\n");	
	}
    // resource release
    if (fclose(in) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;  
    }
    if (fclose(out) != 0) {
        perror("Failed to close the output file!");
        return EXIT_FAILURE;  
    }
    return EXIT_SUCCESS;
}
