#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;

    // Find the matrix number of lines and columns.
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) return 1;
    int i = 0;
    int j = 0;
    int nlines = 0;
    int ncols = 0;
    char l[256];
    while(fgets(l, sizeof(l), f)) nlines++;
    while(l[ncols] != '\n') ncols++;
    char m[nlines][ncols];
    if (fclose(f)) return 1;

    // Store each character in the matrix.
    f = fopen(argv[1], "r");
    if (f == NULL) return 1;
    while(fgets(l, sizeof(l), f)) {
        j = 0;
        while(l[j] != '\n') {
            m[i][j] = l[j];
            j++;
        }
        i++;
    }
    if (fclose(f)) return 1;

    char mremoved[nlines][ncols];
    for (i = 0; i < nlines; ++i) {
        for (j = 0; j < ncols; ++j) {
            mremoved[i][j] = '.';
        }
    }
    // we assume removed is not 0 in order for while loop to start
    int removed = 1;
    int res = 0;
    while (removed) {
        removed = 0;
        for (i = 0; i < nlines; ++i) {
            for (j = 0; j < ncols; ++j) {
                if (m[i][j] != '@') continue;
                int count = 0;
                // Handle top part
                if (i > 0) {
                    if (j > 0) {
                        if (m[i-1][j-1] == '@') count++;
                    }
                    if (j < ncols-1) {
                        if (m[i-1][j+1] == '@') count++;
                    }
                    if (m[i-1][j] == '@') count++;
                }
                // Handle center
                if (j > 0) {
                    if (m[i][j-1] == '@') count++;
                }
                if (j < ncols-1) {
                    if (m[i][j+1] == '@') count++;
                }
                // Handle bottom part
                if (i < nlines-1) {
                    if (j > 0) {
                        if (m[i+1][j-1] == '@') count++;
                    }
                    if (j < ncols-1) {
                        if (m[i+1][j+1] == '@') count++;
                    }
                    if (m[i+1][j] == '@') count++;
                }
                if (count < 4) {
                    mremoved[i][j] = 'x';
                    removed++;
                }
            }
        }
        // Match the removed rolls of paper
        for (i = 0; i < sizeof(m)/sizeof(m[0]); ++i) {
            for (j = 0; j < sizeof(m[0]); ++j) {
                if (mremoved[i][j] == 'x' && m[i][j] != 'x') {
                    m[i][j] = 'x';
                }
            }
        }
        res += removed;
    }
    printf("res = %d\n", res);

    return 0;
}
