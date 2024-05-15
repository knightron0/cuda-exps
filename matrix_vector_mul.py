import torch 
import sys

matrix_size = int(sys.argv[1])

matrix = torch.arange(matrix_size * matrix_size, dtype=torch.float32).reshape(matrix_size, matrix_size)

vector = torch.arange(matrix_size, dtype=torch.float32).reshape(matrix_size, 1)

result = torch.matmul(matrix, vector)
for element in result:
    print(f"{element.item():.2f}")
