#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Thread-safe random number generation function using rand_r
double drand(unsigned int *seed) {
    return (double)rand_r(seed) / (double)RAND_MAX;
}

int main() {
    int i, count, n;
    double x, y, z, pi;

    printf("n = ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input. Please enter a positive integer.\n");
        return 1;
    }

    count = 0;

    double start_time = omp_get_wtime();

    #pragma omp parallel
    {
        unsigned int seed = (unsigned int)time(NULL) ^ omp_get_thread_num();
        #pragma omp for private(x, y, z) reduction(+:count)
        for (i = 0; i < n; ++i) {
            x = drand(&seed);
            y = drand(&seed);
            z = x * x + y * y;

            if (z <= 1) count++;
        }
    }

    double end_time = omp_get_wtime();

    pi = (double)count / n * 4;

    double elapsed_time = end_time - start_time;

    printf("Approximate PI = %g\n", pi);
    printf("Time taken = %f seconds\n", elapsed_time);

    return 0;
}
