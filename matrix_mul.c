#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void matmul(float *a, float *b, float*res, int n, int m, int k) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            float sum = 0.0;
            for (int ii = 0; ii < m; ii++) {
                sum += a[i * m + ii] * b[ii * k + j];
            }
            res[i * k + j] = sum;
        }
    }
}

int main(int argc, char **argv) {
    int n, m, k;

    // (n x m) x (m x k) -> (n x k)

    float *a, *b, *res; 
    n = atoi(argv[1]); m = atoi(argv[2]); k = atoi(argv[3]);
    
    a = (float *) malloc(n * m * sizeof(float));
    b = (float *) malloc(m * k * sizeof(float));
    res = (float *) malloc(n * k * sizeof(float));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            a[i * m + j] = (float) i * m + j;
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            b[i * k + j] = (float) (m * k - 1) - (i * k + j);
        }
    }
    
    matmul(a, b, res, n, m, k);
    
    printf("a: \n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%f ", a[i * m + j]);
        }
        printf("\n");
    }
    printf("\nb: \n");
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            printf("%f ", b[i * k + j]);
        }
        printf("\n");
    }
    printf("\nres: \n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            printf("%f ", res[i * k + j]);
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}