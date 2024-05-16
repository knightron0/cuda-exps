#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void matrix_vector_product(long long int *a, long long int *v, long long int *res, int matrix_size) {
    for (int i = 0; i < matrix_size; i++) {
        long long int sum = 0;
        for (int j = 0; j < matrix_size; j++) {
            sum += a[i * matrix_size + j] * v[j];
        } 
        res[i] = sum;
    }
}

int main(int argc, char **argv) {
    long long int *a, *v, *res; 
    int matrix_size = atoi(argv[1]);
    
    a = (long long int *) malloc(matrix_size * matrix_size * sizeof(long long int));
    v = (long long int *) malloc(matrix_size * sizeof(long long int));
    res = (long long int *) malloc(matrix_size * sizeof(long long int));
    
    // printf("a: ");
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            a[i * matrix_size + j] = (long long int) i * matrix_size + j;
            // printf("%lld ", a[i * matrix_size + j]);
        }
        // printf("\n");
        v[i] = (long long int) i;
    }
    // printf("v: ");
    // for (int i = 0; i < matrix_size; i++) {
    //     printf("%lld ", v[i]);
    // }
    // printf("\n");

    clock_t st, en;
    st = clock();
    matrix_vector_product(a, v, res, matrix_size);
    en = clock();

    for (int i = 0; i < matrix_size; i++) {
        printf("%lld\n", res[i]);
    }
    
    printf("Time taken by CPU: %f seconds\n", (double)(en - st) / CLOCKS_PER_SEC);

    free(a);
    free(v);
    free(res);

    return 0;
}