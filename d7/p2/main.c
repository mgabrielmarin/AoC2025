// I solved this using the hint provieded in this url:
// https://www.reddit.com/r/adventofcode/comments/1pgb377/2025_day_7_part_2_hint/
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) return 1;

    char l[256];
    static char m[256][256];
    int i = 0;
    while (fgets(l, sizeof(l), f)) {
        for (int j = 0; l[j] != '\n'; ++j) {
            m[i][j] = l[j];
        }
        i++;
    }
    int nlines = i;

    int j = 0;
    for (i = 0; i < nlines; ++i) {
        j = 0;
        while (m[i][j]) {
            if (m[i][j] == 'S') {
                m[i+1][j] = '|';
            }
            if (m[i][j] == '.' ) {
                if (m[i-1][j] == '|') {
                    m[i][j] = '|';
                }
            } else if (m[i][j] == '^') {
                if (m[i-1][j] == '|') {
                    if (j > 0) m[i][j-1] = '|';
                    if (m[i][j+1] != 0) m[i][j+1] = '|';
                }
            }
            j++;
        }
    }

    static unsigned long sums[256][256];
    for (int i = 0; i < 256; ++i) {
        for (int j = 0; j < 256; ++j) {
            if (m[i-1][j] == 'S') sums[i][j]++;
            if (m[i][j] == '^' && m[i-1][j] == '|') {
                sums[i][j-1] += sums[i-1][j];
                sums[i][j+1] += sums[i-1][j];
            }
            if (m[i][j] == '|' && m[i-1][j] == '|') {
                if (sums[i][j] == 0) {
                    sums[i][j] = sums[i-1][j];
                } else {
                    sums[i][j] += sums[i-1][j];
                }
            }
        }
    }

    unsigned long res = 0;
    for (int i = 0; i < 256; ++i) {
        res += sums[nlines-1][i];
    }
    printf("res = %lu\n", res);

    if (fclose(f)) return 1;

    return 0;
}
