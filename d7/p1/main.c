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

    for (i = 0; i < nlines; ++i) {
        j = 0;
        while (m[i][j]) {
            printf("%c", m[i][j]);
            j++;
        }
        printf("\n");
    }

    int res = 0;
    for (i = 0; i < nlines; ++i) {
        j = 0;
        while (m[i][j]) {
            if (m[i][j] == '^' && m[i-1][j] == '|') {
                if (m[i][j-1] == '|' && m[i][j+1] == '|') {
                    res += 1;
                }
            }
            j++;
        }
    }
    printf("res = %d\n", res);

    if (fclose(f)) return 1;

    return 0;
}
