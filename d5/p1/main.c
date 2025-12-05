#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) return 1;

    // Store ranges
    static unsigned long long lows[256];
    static unsigned long long highs[256];
    int i = 0;
    char l[64];
    while(fgets(l, sizeof(l), f)) {
        if (!isdigit(l[0])) break;
        char *pl = l;
        lows[i] = atoll(strsep(&pl, "-"));
        highs[i] = atoll(strsep(&pl, "\n"));
        i++;
    }
    int nranges = i;

    // Store ids
    i = 0;
    static unsigned long long ids[256];
    while(fgets(l, sizeof(l), f)) {
        char *pl = l;
        ids[i] = atoll(strsep(&pl, "\n"));
        i++;
    }
    int nids = i;

    // Calculate fresh ids
    int j = 0;
    int res = 0;
    for (i = 0; i < nids; ++i) {
        for (j = 0; j < nranges; ++j) {
            if (ids[i] >= lows[j] && ids[i] <= highs[j]) {
                res++;
                break;
            }
        }
    }
    printf("res = %d\n", res);

    if (fclose(f)) return 1;

    return 0;
}
