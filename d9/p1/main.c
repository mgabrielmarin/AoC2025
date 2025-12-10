#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NLINES 512

struct point {
    long x;
    long y;
};

struct area {
    long dx;
    long dy;
    long val;
};

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) return 1;

    char l[NLINES];
    static struct point ps[NLINES];
    int i = 0;
    while (fgets(l, sizeof(l), f)) {
        char *pl = l;
        ps[i].x = atol(strsep(&pl, ","));
        ps[i].y = atol(strsep(&pl, ","));
        i++;
    }
    int npoints = i;

    int nareas = (npoints * (npoints-1)) / 2;
    struct area areas[nareas];
    int k = 0;
    for (int i = 0; i < npoints; ++i) {
        for (int j = i+1; j < npoints; ++j) {
            if (ps[i].x < ps[j].x) {
                areas[k].dx = (ps[j].x - ps[i].x + 1);
            } else {
                areas[k].dx = (ps[i].x - ps[j].x + 1);
            }

            if (ps[i].y < ps[j].y) {
                areas[k].dy = (ps[j].y - ps[i].y + 1);
            } else {
                areas[k].dy = (ps[i].y - ps[j].y + 1);
            }
            areas[k].val = areas[k].dx * areas[k].dy;
            k++;
        }
    }

    long res = 0;
    for (int i = 0; i < nareas; ++i) {
        if (res < areas[i].val) res = areas[i].val;
    }
    printf("res = %ld\n", res);

    if (fclose(f)) return 1;

    return 0;
}
