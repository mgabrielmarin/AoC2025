#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void helper(char *from, int i, char *to, int j) {
    if (j == 12) {
        to[j] = 0;
        return;
    }
    int k = i+1;
    while(isdigit(from[k])) {
        if (from[i] < from[k] && isdigit(from[k+11-j])) {
            i = k;
        }
        k++;
    }
    to[j] = from[i];
    i++;
    j++;
    helper(from, i, to, j);
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) return 1;

    unsigned long long res = 0;
    char l[256];
    while(fgets(l, sizeof(l), f)) {
        char buf[13];
        helper(l, 0, buf, 0);
        res += atoll(buf);
    }
    printf("res = %llu\n", res);
    if (fclose(f)) return 1;

    return 0;
}
