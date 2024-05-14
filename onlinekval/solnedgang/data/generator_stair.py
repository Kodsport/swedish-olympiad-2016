import sys
import random

if len(sys.argv) != 5:
    sys.stderr.write('Wrong number of arguments\n')
    sys.exit(1)

(n_max, xy_max, variant, seed) = [int(s) for s in sys.argv[1:]]


random.seed(seed)

n = n_max
k = 20
x_offset = 0
y_offset = 0


def write_output(houses, k):
    s = str(len(houses)) + " " + str(k) + '\n'
    for house in houses:
        s += str(house[0]) + " " + str(house[1]) + '\n'
    return s.strip()


def stair(x, y, step, n):
    buildings = []
    for i in range(0, n):
        buildings.append((x + i, y + step * i))
    return buildings

poison = False
if n > 100:
    poison = True
    n -= 4

if variant == 0:
    buildings = stair(x_offset, y_offset, 1, n)
elif variant == 1:
    # Cannot be solved
    buildings = stair(x_offset, y_offset, 1, n // 2) + stair(x_offset, y_offset + 10, 1, n // 2)
elif variant == 2:
    # Can be solved
    buildings = stair(x_offset, y_offset, 2, n // 2) + stair(x_offset, y_offset + 10, 2, n // 2)
elif variant == 3:
    # Can be solved
    buildings = stair(x_offset, y_offset + 3, 2, n // 2) + stair(x_offset, y_offset, 2, n // 2)
elif variant == 4:
    # Cannot be solved
    buildings = stair(x_offset, y_offset, 2, n // 2) + stair(x_offset, y_offset + 3, 2, n // 2)
elif variant == 5:
    k = 5
    n0 = n // 4
    # Can be solved
    buildings = stair(x_offset, y_offset + 7, 1, n0)
    buildings = buildings + stair(x_offset + 1, y_offset + 5, 1, n0)
    buildings = buildings + stair(x_offset, y_offset + 1, 1, n0)
    buildings = buildings + stair(x_offset + 3, y_offset, 1, n0)
else:
    exit(1)

if poison:
    seen = set()
    for b in buildings:
        seen.add(b)

    additional = [(0, 0), (xy_max, 0), (0, xy_max), (xy_max, xy_max)]
    for a in additional:
        if a not in seen and (a[0], a[1] + 1) not in seen and (a[0], a[1] - 1) not in seen:
            buildings.append(a)

print(write_output(buildings, k))
