#!/usr/bin/python3

n = [*map(int,[*input()])]

i = len(n)-2

while i >= 0:
    if n[i] < 9:
        bestind = -1
        for j in range(i+1,len(n)):
            if n[j] > 0:
                if bestind == -1 or n[bestind] > n[j]:
                    bestind = j

        if bestind != -1:
            j = bestind
            n[i] += 1
            n[j] -= 1

            n[i+1:] = sorted(n[i+1:])
            break
    i -= 1
else:
    m = 9
    for x in n:
        if x != 0:
            m = min(x,m)
    
    n[n.index(m)] -= 1
    n.sort()
    n = [1] + n

print("".join(map(str,n)))