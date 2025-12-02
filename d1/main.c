#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) return 1;

    int dial = 50;
    int count = 0;
    char l[10];
    while (fgets(l, sizeof(l), f)) {
        int n = atoi(l+1);
        if (l[0] == 'R') {
            dial += n;
        } else if (l[0] == 'L') {
            dial -= n;
        }
        dial %= 100;
        if (dial < 0) dial += 100;
        if (dial == 0) count++;
    }
    if (fclose(f)) return 1;
    printf("count = %d\n", count);

    return 0;
}
