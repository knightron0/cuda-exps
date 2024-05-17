import torch 
import sys

matrix_size = int(sys.argv[1])

matrix = torch.arange(matrix_size * matrix_size, dtype=torch.float32).reshape(matrix_size, matrix_size)

vector = torch.arange(matrix_size, dtype=torch.float32).reshape(matrix_size, 1)

result = torch.matmul(matrix, vector)

# print("a: ", end="")
# for row in matrix:
#     print(" ".join(f"{element.item()}" for element in row), end=" \n")
# print("v: ", end="")
# for element in vector:
#     print(f"{element.item()} ", end="")
# print()
for element in result:
    print(f"{element.item():.2f}")
