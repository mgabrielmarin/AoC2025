// Sadly used gemini for the final part involving DSU
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define NLINES 1000
#define NCOORDS 3

struct distances {
    int p;
    int q;
    long long d;
};

int parent[NLINES];
int circuit_sizes[NLINES];

void dsu_init() {
    for (int i = 0; i < NLINES; ++i) {
        parent[i] = i;
        circuit_sizes[i] = 1;
    }
}

int dsu_find(int i) {
    if (parent[i] == i) return i;
    return parent[i] = dsu_find(parent[i]);
}

void dsu_union(int i, int j) {
    int root_i = dsu_find(i);
    int root_j = dsu_find(j);

    if (root_i != root_j) {
        if (circuit_sizes[root_i] < circuit_sizes[root_j]) {
            parent[root_i] = root_j;
            circuit_sizes[root_j] += circuit_sizes[root_i];
        } else {
            parent[root_j] = root_i;
            circuit_sizes[root_i] += circuit_sizes[root_j];
        }
    }
}

int cmpdist(const void *d1, const void *d2) {
    long long distance1 = ((struct distances *)d1)->d;
    long long distance2 = ((struct distances *)d2)->d;
    if (distance1 < distance2) return -1;
    if (distance1 > distance2) return 1;
    return 0;
}

int cmpcirc(const void *c1, const void *c2) {
    if (*((unsigned int *)c1) < *((unsigned int *)c2)) return 1;
    if (*((unsigned int *)c1) > *((unsigned int *)c2)) return -1;
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;

    FILE *f = fopen(argv[1], "r");
    if (f == NULL) return 1;

    char l[64];
    static long nums[NLINES][NCOORDS];
    int i = 0;
    while (fgets(l, sizeof(l), f)) {
        char *pl = l;
        char *n;
        int j = 0;
        while((n = strsep(&pl, ",")) != NULL) {
            nums[i][j] = atol(n);
            j++;
        }
        i++;
    }

    long ndistances = (NLINES * (NLINES-1)) / 2;
    struct distances *ds = malloc(sizeof(struct distances) * ndistances);
    int d = 0;
    for (int i = 0; i < NLINES; ++i) {
        for (int j = i+1; j < NLINES; ++j) {
            long long distance = 0;
            long long diff;
            for (int k = 0; k < NCOORDS; ++k) {
                diff = nums[i][k] - nums[j][k];
                distance += diff * diff;
            }
            ds[d].p = i;
            ds[d].q = j;
            ds[d].d = distance;
            d++;
        }
    }
    qsort(ds, ndistances, sizeof(struct distances), cmpdist);

    // Disjoint Set Union (DSU)
    dsu_init();
    for (int i = 0; i < NLINES; ++i) {
        int p = ds[i].p;
        int q = ds[i].q;
        dsu_union(p,q);
    }

    unsigned int valid_circuit_sizes[NLINES];
    int nvalid_circuit_sizes = 0;
    for (int i = 0; i < NLINES; ++i) {
        if (parent[i] == i) {
            valid_circuit_sizes[nvalid_circuit_sizes++] = circuit_sizes[i];
        }
    }
    qsort(valid_circuit_sizes, nvalid_circuit_sizes,
           sizeof(unsigned int), cmpcirc);

    unsigned int res = 1;
    for (int i = 0; i < 3; ++i) {
        printf("%u ", valid_circuit_sizes[i]);
        res *= valid_circuit_sizes[i];
    }
    printf("res = %u\n", res);

    if (fclose(f)) return 1;

    return 0;
}
