#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SEED time(NULL)

int main() {
    srand(SEED);
    int i, count, n;
    double x, y, z, pi;

    printf("n = ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    count = 0;

    clock_t start = clock();

    for (i = 0; i < n; ++i) {
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        z = x * x + y * y;

        if (z <= 1) count++;
    }

    clock_t end = clock();

    pi = (double)count / n * 4;

    double elapsed_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Approximate PI = %g\n", pi);
    printf("Time taken = %f seconds\n", elapsed_time);

    return 0;
}
