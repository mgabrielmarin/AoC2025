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
    while (fgets(l, sizeof(l), f)) nlines++;
    char *pl = l;
    char *c;
    while ((c = strsep(&pl, " ")) != NULL) {
        if (*c == '+' || *c == '*')
            ncols++;
    }
    if (fclose(f)) return 1;

    // Store data
    f = fopen(argv[1], "r");
    if (f == NULL) return 1;

    int i = 0;
    char nums[nlines][4096];
    while (fgets(l, sizeof(l), f)) {
        strncpy(nums[i], l, 4096);
        i++;
    }

    unsigned long res = 0;
    int n = 0;
    char op = 0;
    for (int j = 0; j < 4096; ++j) {
        int k = 0;
        static char num[32];
        unsigned long acc = 0;
        static unsigned long lnums[4098];
        for (int i = 0; i < nlines; ++i) {
            if (isnumber(nums[i][j])) {
                num[k++] = nums[i][j];
            }
        }
        num[k] = 0;
        if (k != 0) {
            lnums[n] = atol(num);
            n++;
        }
        if (nums[nlines-1][j] == '+') {
            op = '+';
        } else if (nums[nlines-1][j] == '*') {
            op = '*';
        }
        if (k == 0) {
            if (op == '+') {
                acc = 0;
                while (n-1 >= 0) {
                    if (lnums[n-1]) acc += lnums[n-1];
                    lnums[n-1] = 0;
                    n--;
                }
                op = 0;
            } else if (op == '*') {
                acc = 1;
                while (n-1 >= 0) {
                    if (lnums[n-1]) acc *= lnums[n-1];
                    lnums[n-1] = 0;
                    n--;
                }
                op = 0;
            }
        }
        res += acc;
    }
    printf("res = %lu\n", res);

    if (fclose(f)) return 1;

    return 0;
}
