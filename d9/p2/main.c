// Used Gemini (sadly)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NLINES 512

struct point {
    long x;
    long y;
};

struct rectangle {
    long xmin;
    long xmax;
    long ymin;
    long ymax;
};

long area(struct rectangle r) {
    return 0;
}

int interior_intersects(struct point p1, struct point p2, struct rectangle r) {
    // Horizontal segment
    if (p1.y == p2.y) {
        long xmin = (p1.x < p2.x) ? p1.x : p2.x;
        long xmax = (p1.x > p2.x) ? p1.x : p2.x;

        if (p1.y > r.ymin && p1.y < r.ymax) {
            if (xmin < r.xmax && xmax > r.xmin) {
                return 1;
            }
        }
    }
    // Vertical segment
    else if (p1.x == p2.x) {
        long ymin = (p1.y < p2.y) ? p1.y : p2.y;
        long ymax = (p1.y > p2.y) ? p1.y : p2.y;

        if (p1.x > r.xmin && p1.x < r.xmax) {
            if (ymin < r.ymax && ymax > r.ymin) {
                return 1;
            }
        }
    }
    return 0;
}

int cross_product(struct point p, struct point p1, struct point p2) {
    return (p1.x - p.x) * (p2.y - p.y) - (p1.y - p.y) * (p2.x - p.x);
}

int segment_intersects(struct point p, struct point p1, struct point p2) {
    if (cross_product(p, p1, p2) == 0) {
        return (p.x <= (p1.x > p2.x ? p1.x : p2.x) &&
                p.x >= (p1.x < p2.x ? p1.x : p2.x) &&
                p.y <= (p1.y > p2.y ? p1.y : p2.y) &&
                p.y >= (p1.y < p2.y ? p1.y : p2.y));
    }
    return 0;
}

int is_inside(struct point p, struct point ps[], int npoints) {
    int crossings = 0;

    for (int i = 0; i < npoints; ++i) {
        struct point p1 = ps[i];
        struct point p2 = ps[(i+1)%npoints];

        if (segment_intersects(p, p1, p2)) {
            return 1;
        }

        if (p1.y == p2.y) continue;

        if (p1.y > p2.y) {
            struct point tmp = p1;
            p1 = p2;
            p2 = tmp;
        }

        if (p.y >= p1.y && p.y < p2.y) {
            if (p.x < p1.x + (p2.x - p1.x) * (p.y - p1.y) / (p2.y - p1.y)) {
                crossings++;
            }
        }
    }
    return (crossings % 2 == 1);
}

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

    long res = 0;
    for (int i = 0; i < npoints; ++i) {
        for (int j = i+1; j < npoints; ++j) {
            struct rectangle r;
            r.xmin = ps[i].x < ps[j].x ? ps[i].x : ps[j].x;
            r.xmax = ps[i].x > ps[j].x ? ps[i].x : ps[j].x;
            r.ymin = ps[i].y < ps[j].y ? ps[i].y : ps[j].y;
            r.ymax = ps[i].y > ps[j].y ? ps[i].y : ps[j].y;

            long dx = r.xmax - r.xmin + 1;
            long dy = r.ymax - r.ymin + 1;
            long a = dx * dy;

            int valid = 1;
            for (int k = 0; k < npoints; ++k) {
                struct point p1 = ps[k];
                struct point p2 = ps[(k+1)%npoints];
                if (interior_intersects(p1, p2, r)) {
                    valid = 0;
                    break;
                }
            }
            if (!valid) continue;

            if (dx > 2 && dy > 2) {
                struct point ptest = {r.xmin+1,r.ymin+1};
                if (!is_inside(ptest, ps, npoints)) {
                    valid = 0;
                }
            }

            if (valid) {
                if (res < a) res = a;
            }
        }
    }
    printf("res = %ld\n", res);

    if (fclose(f)) return 1;

    return 0;
}
