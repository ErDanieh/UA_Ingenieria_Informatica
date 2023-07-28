import numpy as np

v1 = np.ones(10)*4
print(v1)

mat1= np.ones((3,5))
print(mat1)

v2 = np.arange(10)
print(v2)

prod = v1 * v2

print(prod)
print(np.sum(prod))

mat3 = np.ones((2,3,6))
print(mat3)
print("xxxxxxxxxxxxxxxxxxxxxxxxx")
mat3 = mat3.reshape(2,18)
print(mat3)
print("xxxxxxxxxxxxxxxxxxxxxxxxx")
mat4 = np.ones((2,2))
mat5 = mat4.reshape(1,4)
print(mat4)
print("xxxxxxxxxxxxxxxxxxxxxxxxx")
print(mat5)