#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;

    // Find the matrix number of lines and columns.
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) return 1;
    int i = 0;
    int j = 0;
    char l[256];
    while(fgets(l, sizeof(l), f)) i++;
    while(l[j] != '\n') j++;
    char m[i][j];
    if (fclose(f)) return 1;

    // Store each character in the matrix.
    f = fopen(argv[1], "r");
    if (f == NULL) return 1;
    i = 0;
    while(fgets(l, sizeof(l), f)) {
        j = 0;
        while(l[j] != '\n') {
            m[i][j] = l[j];
            j++;
        }
        i++;
    }
    if (fclose(f)) return 1;

    int res = 0;
    for (i = 0; i < sizeof(m)/sizeof(m[0]); ++i) {
        for (j = 0; j < sizeof(m[0]); ++j) {
            if (m[i][j] != '@') continue;
            int count = 0;
            // Handle top part
            if (i > 0) {
                if (j > 0) {
                    if (m[i-1][j-1] == '@') count++;
                }
                if (j < sizeof(m[0])-1) {
                    if (m[i-1][j+1] == '@') count++;
                }
                if (m[i-1][j] == '@') count++;
            }
            // Handle center
            if (j > 0) {
                    if (m[i][j-1] == '@') count++;
            }
            if (j < sizeof(m[0])-1) {
                if (m[i][j+1] == '@') count++;
            }
            // Handle bottom part
            if (i < (sizeof(m)/sizeof(m[0]))-1) {
                if (j > 0) {
                    if (m[i+1][j-1] == '@') count++;
                }
                if (j < sizeof(m[0])-1) {
                    if (m[i+1][j+1] == '@') count++;
                }
                if (m[i+1][j] == '@') count++;
            }
            if (count < 4) res++;
        }
    }
    printf("res = %d\n", res);

    return 0;
}
