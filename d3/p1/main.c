#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    FILE *f = fopen(argv[1], "r");

    unsigned int res = 0;
    char l[256];
    while(fgets(l, sizeof(l), f)) {
        int i = 0;
        int j = 1;
        int k = 1;
        while (l[k] != '\n') {
            if (l[i] < l[k] && l[k+1] != '\n') {
                i = k;
                j = k+1;
            } else if(l[j] < l[k]) {
                j = k;
            }
            k++;
        }
        char buf[3]; // Two chars and null terminator 'cc0'
        snprintf(buf, sizeof(buf), "%c%c", l[i], l[j]);
        res += atoi(buf);
    }
    printf("res = %u\n", res);
    if (fclose(f)) return 1;

    return 0;
}
