#include <stdio.h>

__global__ void hello_cuda() {
    printf("Hello from CUDA\n");
    printf("Block Index X: %d, Block Index Y: %d, Thread Index X: %d, Thread Index Y: %d\n", blockIdx.x, blockIdx.y, threadIdx.x, threadIdx.y);
}

int main() {
    hello_cuda<<<2, 2>>>();
    cudaDeviceSynchronize();

    return 0;
}