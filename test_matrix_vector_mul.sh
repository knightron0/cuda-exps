#! /bin/bash

gcc matrix_vector_mul.c -o matrix_vector_mul
nvcc matrix_vector_mul.cu -o cuda_matrix_vector_mul

./matrix_vector_mul $1 > cpu_out
./cuda_matrix_vector_mul $1 > gpu_out
python3 -W ignore matrix_vector_mul.py $1 > py_out

echo "comparing CPU and GPU:"
diff cpu_out gpu_out
# echo
# echo "comparing CPU and Python:"
# diff cpu_out py_out
# echo
# echo "comparing GPU and Python:"
# diff gpu_out py_out