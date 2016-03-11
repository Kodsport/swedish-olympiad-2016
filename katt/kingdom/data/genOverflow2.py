print(8, 2)
ar = [5 << 27] * 8
ar[0] = 1 << 27
print(" ".join(map(str, ar)))
print(" ".join(str(i) for i in range(7)))
print(" ".join(str(i+1) for i in range(7)))
