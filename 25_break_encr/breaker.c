#include<stdlib.h>
#include<stdio.h>
#include <ctype.h>

int main(int argc, char ** argv) {
    if (argc != 2) {
        fprintf(stderr, "argument number error\n");
        return EXIT_FAILURE;
    }
    // Observe
    int cnt[26] = {0};          // must initialize
    FILE* file = fopen(argv[1], "r+");
    if (file == NULL) {
        fprintf(stderr, "open file(%s) error\n", argv[1]);
        return EXIT_FAILURE;
    }
    int ch = 0;                 // must initialize
    int E = 0;                  // must initialize
    int maxFrq = 0;
    while ((ch = fgetc(file)) != EOF) {
        if ('A' <= ch && ch <= 'Z') {
            ch = tolower(ch);
        }
        if (ch < 'a' || 'z' < ch) {
            continue;
        }
        int idx = ch-'a';
        cnt[idx]++;
        if (cnt[idx] > maxFrq) {
            E = ch;
            maxFrq = cnt[idx];
        }
    }
    printf("%d\n", (E - 'e') % 26);

    if (fclose(file) != 0) {
       fprintf(stderr, "Failed to close the input file!\n");
       return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
