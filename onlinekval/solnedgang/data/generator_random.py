# Usage: python generator_random.py n_max xy_max seed_offset seed

import random
import sys

if len(sys.argv) != 5:
    print('Wrong number of arguments')
    sys.exit(1)

(n_max, xy_max, seed_offset, seed) = [int(s) for s in sys.argv[1:]]
seed += seed_offset

random.seed(seed)

seen = set()

k = random.randrange(0, xy_max)
n = random.randrange(0, n_max)
houses = []
x_min = random.randrange(0, xy_max)
x_max = random.randrange(x_min, xy_max)
x_max = min(x_max - x_min, n) + x_min

for x in range(x_min, x_max + 1):
    n_in_col = random.randrange(1, 5)

    for i in range(0, n_in_col):
        y = random.randrange(0, 30)

        if (x, y) in seen or (x, y - 1) in seen or (x, y + 1) in seen:
            continue

        seen.add((x, y))
        houses.append((x, y))


print(str(len(houses)) + " " + str(k))
for house in houses:
    print(str(house[0]) + " " + str(house[1]))
