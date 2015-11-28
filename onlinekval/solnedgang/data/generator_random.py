#Usage: python generator_random.py n_min n_max r_min r_max seed

import random
import sys

if len(sys.argv) != 6:
    print 'Wrong number of arguments'
    sys.exit(1)
s = int(sys.argv[5])
random.seed(s)
n = random.randint(int(sys.argv[1]), int(sys.argv[2]))
r = random.randint(int(sys.argv[3]), int(sys.argv[4]))
m = int(random.random()*r*r*2) + 1
a = [random.random()*360 for _ in range(n)]
print "{} {} {}".format(n, m, r)
print ' '.join(map(str, a))
