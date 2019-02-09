import numpy as np
import numpy.linalg as LA

print("Input the dimension of matrix:")

N = input()

a = [[1./(y+x+1.) for y in range(N)] for x in range(N)]

print(a[0])
print(a[1])
print(a[2])
print(a[3])

eig_decomp = LA.eig(a)

S = eig_decomp[0]

V = eig_decomp[1]

print(S)
print()
print(V)
