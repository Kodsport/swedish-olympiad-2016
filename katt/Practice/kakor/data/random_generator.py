import sys
import random

random.seed(int(sys.argv[3]))

N = int(sys.argv[1])
max_a = int(sys.argv[2])

A = [str(random.randint(1, max_a)) for i in range(N)]
print(N)
print(' '.join(A))
