#include <stdio.h>
#include <stdlib.h>
#include <time.h>

__global__ void matrix_vector_product(float *a, float *v, float *res, int matrix_size) {
    float sum = 0.0;
    for (int j = 0; j < blockDim.x; j++) {
        sum += a[threadIdx.x * blockDim.x + j] * v[j];
    } 
    res[threadIdx.x] = sum;
}

int main(int argc, char **argv) {
    float *a, *v, *res; 
    float *a_gpu, *v_gpu, *res_gpu;
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

    cudaMalloc((void **) &a_gpu, matrix_size * matrix_size * sizeof(float));
    cudaMalloc((void **) &v_gpu, matrix_size * sizeof(float));
    cudaMalloc((void **) &res_gpu, matrix_size * sizeof(float));

    cudaMemcpy(a_gpu, a, matrix_size * matrix_size * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(v_gpu, v, matrix_size * sizeof(float), cudaMemcpyHostToDevice);

    clock_t st, en;
    st = clock();
    matrix_vector_product<<<1, matrix_size>>>(a_gpu, v_gpu, res_gpu, matrix_size);
    en = clock();

    cudaMemcpy(res, res_gpu, matrix_size * sizeof(float), cudaMemcpyDeviceToHost);

    for (int i = 0; i < matrix_size; i++) {
        printf("%.2f\n", res[i]);
    }
    
    printf("Time taken by GPU: %f seconds\n", (double)(en - st) / CLOCKS_PER_SEC);

    free(a);
    free(v);
    free(res);
    cudaFree(a_gpu);
    cudaFree(v_gpu);
    cudaFree(res_gpu);

    return 0;
}