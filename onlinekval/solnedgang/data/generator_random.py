# Usage: python generator_random.py n_max xy_max seed_offset seed solver_path

import random
import sys
from subprocess import check_output

if len(sys.argv) != 5:
    print('Wrong number of arguments')
    sys.exit(1)

(n_max, k_max, xy_max, seed) = [int(s) for s in sys.argv[1:]]
solver_path = "./solver"

random.seed(seed)

# 50% probability of k_max
k = min(random.randrange(0, k_max * 2), k_max)
# 50% probability of n_max
n = min(random.randrange(0, n_max * 2), n_max)


def write_output(houses, k):
    s = str(len(houses)) + " " + str(k) + '\n'
    for house in houses:
        s += str(house[0]) + " " + str(house[1]) + '\n'
    return s

houses = []
x_min = random.randrange(0, xy_max)
x_max = random.randrange(x_min, xy_max)
x_max = min(x_max - x_min, (n - 1) // 5) + x_min

temp_houses = []
x = x_min
prev_x = x
seen = set()
prev_min = random.randrange(1, xy_max)
prev_max = prev_min

while x <= x_max:
    n_in_col = 5 if xy_max > 100 else 2

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
        # sys.stderr.write(str(k) + " " + str(n - len(houses) - len(temp_houses)) + " " + str(len(temp_houses)) + " " + str(x) + " " + str(works) + "\n")
        if works:
            houses = houses + temp_houses
            temp_houses = []
            prev_x = x

            if n_in_col == 0:
                break
        else:
            x = prev_x
            temp_houses = []

    seen.clear()

    for i in range(0, n_in_col):
        if i == 0:
            y = random.randrange(max(prev_min - k, 0), min(prev_max + k, xy_max))
            prev_min = prev_max = y
        else:
            y = random.randrange(0, xy_max)

        if y in seen or y - 1 in seen or y + 1 in seen:
            continue

        seen.add(y)
        temp_houses.append((x, y))

    x += 1

houses = houses + temp_houses

print(write_output(houses, k).strip())
