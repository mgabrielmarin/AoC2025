#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) return 1;

    // Find number of lines and number of columns
    char l[4096];
    static unsigned int nlines;
    static unsigned int ncols;
    while(fgets(l, sizeof(l), f)) nlines++;
    char *pl = l;
    char *c;
    while ((c = strsep(&pl, " ")) != NULL) {
        if (*c == '+' || *c == '*')
            ncols++;
    }
    if (fclose(f)) return 1;

    // Store data
    unsigned long nums[nlines-1][ncols];
    char ops[ncols];
    f = fopen(argv[1], "r");
    if (f == NULL) return 1;
    int i = 0;
    int j = 0;
    while (fgets(l, sizeof(l), f)) {
        j = 0;
        pl = l;
        int k = 0;
        while (l[k] != '\n') k++;
        l[k] = 0;
        while ((c = strsep(&pl, " ")) != NULL) {
            if (*c == '+' || *c == '*') {
                ops[j] = *c;
                j++;
            } else if (isnumber(*c)) {
                nums[i][j] = atol(c);
                j++;
            }
        }
        i++;
    }

    unsigned long ares[ncols];
    for (j = 0; j < ncols; ++j) {
        if (ops[j] == '+') {
            ares[j] = 0;
        } else if (ops[j] == '*') {
            ares[j] = 1;
        }
        for (i = 0; i < nlines - 1; ++i) {
            if (ops[j] == '+') {
                ares[j] += nums[i][j];
            } else if (ops[j] == '*') {
                ares[j] *= nums[i][j];
            }
        }
    }

    unsigned long res = 0;
    for (i = 0; i < ncols; ++i) {
        res += ares[i];
    }
    printf("res = %lu\n", res);

    if (fclose(f)) return 1;

    return 0;
}
