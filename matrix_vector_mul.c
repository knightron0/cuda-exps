#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void matrix_vector_product(float *a, float *v, float *res, int matrix_size) {
    for (int i = 0; i < matrix_size; i++) {
        float sum = 0.0;
        for (int j = 0; j < matrix_size; j++) {
            sum += a[i * matrix_size + j] * v[j];
        } 
        res[i] = sum;
    }
}

int main(int argc, char **argv) {
    float *a, *v, *res; 
    int matrix_size = atoi(argv[1]);
    
    a = (float *) malloc(matrix_size * matrix_size * sizeof(float));
    v = (float *) malloc(matrix_size * sizeof(float));
    res = (float *) malloc(matrix_size * sizeof(float));
    
    for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            a[i * matrix_size + j] = (float) i * matrix_size + j;
        }
        v[i] = (float) i;
    }

    clock_t st, en;
    st = clock();
    matrix_vector_product(a, v, res, matrix_size);
    en = clock();

    for (int i = 0; i < matrix_size; i++) {
        printf("%.2f\n", res[i]);
    }
    
    printf("Time taken by CPU: %f seconds\n", (double)(en - st) / CLOCKS_PER_SEC);

    free(a);
    free(v);
    free(res);

    return 0;
}