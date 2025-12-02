#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) return 1;

    char in[1024];
    if (fgets(in, sizeof(in), f) == NULL) return 1;
    char *ids;
    char *pin = in;
    unsigned long long res = 0;
    while((ids = strsep(&pin, ",")) != NULL) {
        unsigned long long from = atoll(strsep(&ids, "-"));
        unsigned long long to = atoll(strsep(&ids, "-"));
        int maxldigits = 20;
        for (unsigned long long i = from; i <= to; ++i) {
            char buf[maxldigits];
            snprintf(buf, sizeof(buf), "%llu", i);
            if ((strlen(buf) % 2) == 0) {
                if (strncmp(buf, buf+(strlen(buf)/2), strlen(buf)/2) == 0) {
                    res += i;
                }
            }
        }
    }
    printf("res = %llu\n", res);
    if (fclose(f)) return 1;

    return 0;
}
