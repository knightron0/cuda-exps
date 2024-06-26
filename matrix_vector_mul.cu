#include <stdio.h>
#include <stdlib.h>
#include <time.h>

__global__ void matrix_vector_product(float *a, float *v, float *res, int matrix_size) {
    int index = (blockDim.x * blockIdx.x) + threadIdx.x;
    // index = threadIdx.x;
    if (index < matrix_size) {
        float sum = 0.0;
        for (int j = 0; j < matrix_size; j++) {
            sum += a[index * matrix_size + j] * v[j];
        } 
        res[index] = sum;
        // printf("%d\n", index);
    }
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

    dim3 grid_size(10);
    dim3 block_size((matrix_size / 10) + 1);
    // printf("grid size: %d %d\n", grid_size.x, grid_size.y);
    // printf("block size: %d %d\n", block_size.x, block_size.y);
    clock_t st, en;
    st = clock();
    matrix_vector_product<<<grid_size, block_size>>>(a_gpu, v_gpu, res_gpu, matrix_size);
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