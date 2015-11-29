# Usage: python generator_random.py n_max xy_max seed_offset seed solver_path

import random
import sys
from subprocess import check_output

if len(sys.argv) != 6:
    print('Wrong number of arguments')
    sys.exit(1)

(n_max, xy_max, seed_offset, seed) = [int(s) for s in sys.argv[1:-1]]
solver_path = sys.argv[-1]

seed += seed_offset

random.seed(seed)


k = random.randrange(0, xy_max) + 100000
n = random.randrange(0, n_max)


def write_output(houses, k):
    s = str(len(houses)) + " " + str(k) + '\n'
    for house in houses:
        s += str(house[0]) + " " + str(house[1]) + '\n'
    return s

houses = []
x_min = random.randrange(0, xy_max)
x_max = random.randrange(x_min, xy_max)
x_max = min(x_max - x_min, n) + x_min

temp_houses = []
x = x_min
prev_x = x
seen = set()
prev_min = random.randrange(1, xy_max)
prev_max = prev_min

while x <= x_max:
    if len(temp_houses) > 0 and (x % 1000 == 0 or x == x_max):
        if len(houses) >= 2:
            partial_houses = [houses[-1]] + houses[-min(10, len(houses)):-1] + temp_houses
        elif len(houses) >= 1:
            partial_houses = [houses[-1]] + temp_houses
        else:
            partial_houses = temp_houses

        partial_input = write_output(partial_houses, k).encode("utf-8")
        solver_output = check_output([solver_path], input=partial_input).decode("utf-8")

        works = solver_output.strip() != "NATT"
        # print(str(x) + ": " + str(works))
        if works:
            houses = houses + temp_houses
            temp_houses = []
            prev_x = x
        else:
            x = prev_x
            temp_houses = []

    n_in_col = random.randrange(1, 5)
    seen.clear()

    for i in range(0, n_in_col):
        if i == 0:
            y = random.randrange(max(prev_min - k, 0), min(prev_max + k, xy_max))
            prev_min = prev_max = y
        else:
            y = random.randrange(0, xy_max)
            prev_min = min(prev_min, y)
            prev_max = max(prev_max, y)

        if y in seen or y - 1 in seen or y + 1 in seen:
            continue

        seen.add(y)
        temp_houses.append((x, y))

    x += 1

houses = houses + temp_houses

print(write_output(houses, k).strip())
