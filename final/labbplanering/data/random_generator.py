import sys
import random

case = sys.argv[1]
pres = int(sys.argv[2])
s = int(sys.argv[3])

random.seed(s)

def t():
    return 11 if case == 'equal' else random.randint(1, 60)

pr = []
while pres > 0:
    npr = 2 if case == 'two' else min(random.choice([1, 2, 2, 3, 4]), pres)
    pres -= npr
    pr.append(npr)

print(len(pr))
for npr in pr:
    ar = [npr] + [t() for _ in range(npr)]
    print(' '.join(map(str, ar)))
