#! /bin/bash

gcc matrix_vector_mul.c -o matrix_vector_mul
nvcc matrix_vector_mul.cu -o cuda_matrix_vector_mul

./matrix_vector_mul $1 > cpu_out
./cuda_matrix_vector_mul $1 > gpu_out

diff cpu_out gpu_out