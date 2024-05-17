#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void matrix_vector_product(long double *a, long double *v, long double *res, int matrix_size) {
    for (int i = 0; i < matrix_size; i++) {
        long double sum = 0;
        for (int j = 0; j < matrix_size; j++) {
            sum += a[i * matrix_size + j] * v[j];
        } 
        res[i] = sum;
    }
}

int main(int argc, char **argv) {
    long double *a, *v, *res; 
    int matrix_size = atoi(argv[1]);
    
    a = (long double *) malloc(matrix_size * matrix_size * sizeof(long double));
    v = (long double *) malloc(matrix_size * sizeof(long double));
    res = (long double *) malloc(matrix_size * sizeof(long double));
    
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            a[i * matrix_size + j] = (long double) i * matrix_size + j;
        }
        v[i] = (long double) i;
    }

    clock_t st, en;
    st = clock();
    matrix_vector_product(a, v, res, matrix_size);
    en = clock();

    for (int i = 0; i < matrix_size; i++) {
        printf("%.2Lf\n", res[i]);
    }
    
    printf("Time taken by CPU: %f seconds\n", (double)(en - st) / CLOCKS_PER_SEC);

    free(a);
    free(v);
    free(res);

    return 0;
}