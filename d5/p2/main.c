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

    // Calculate all valid fresh ids
    unsigned long long res = 0;
    for (int i = 0; i < nranges; ++i) {
        unsigned long long low = lows[i];
        unsigned long long high = highs[i];
        unsigned long long midlow = 0;
        unsigned long long midhigh = 0;
        int counted = 0;
        for (int j = 0; j < i; ++j) {
            if (low < lows[j]) {
                if (high <= highs[j] && high >= lows[j]) {
                    high = lows[j]-1;
                } else if (high > highs[j]) {
                    midlow = lows[j]-1;
                    midhigh = highs[j]+1;
                }
            } else if (low >= lows[j]) {
                if (high <= highs[j]) {
                    counted = 1;
                    break;
                } else if (high >= highs[j] && low <= highs[j]) {
                    low = highs[j]+1;
                }
            }
        }
        if (counted) continue;
        if (midlow == 0 && midhigh == 0) {
            res += high - low + 1;
        } else {
            res += midlow - low + 1;
            res += high - midhigh + 1;
        }
    }
    printf("res = %llu\n", res);

    if (fclose(f)) return 1;

    return 0;
}
