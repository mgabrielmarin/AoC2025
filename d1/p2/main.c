// Used claude (sadly...)
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
        char dir = l[0];

        int full_rotations = n / 100;
        count += full_rotations;

        int remaining = n % 100;
        if (dir == 'L') {
            int new_dial = dial - remaining;
            if (new_dial < 0) {
                if (dial > 0) {
                    count++;
                }
                new_dial += 100;
            }
            dial = new_dial;
        } else {
            int new_dial = dial + remaining;
            if (new_dial >= 100) {
                if (new_dial != 100) {
                    count++;
                }
                new_dial -= 100;
            }
            dial = new_dial;
        }
        if (dial == 0) count++;
    }
    if (fclose(f)) return 1;
    printf("count = %d\n", count);

    return 0;
}
