N,K,M = map(int, raw_input().split())
dice = [0]*N
for i in range(N):
  for c in raw_input():
    dice[i] += 1 << (ord(c) - ord('A'))

def match(index):
  global matched, vis
  if vis[index]:
    return False
  vis[index] = True
  if matched[index] == -1:
    return True
  m = matched[index]
  for j in range(N):
    if (dice[m] & (1 << word[j])) > 0:
      if match(j):
        matched[j] = m
        return True
  return False

res = 0
for w in range(M):
  matched = [-1]*N
  line = raw_input()
  word = map(lambda c: ord(c) - ord('A'), line)
  good = True
  for i in range(N):
    vis = [False]*N
    matchFound = False
    for j in range(N):
      if (dice[i] & (1 << word[j])) > 0:
        if match(j):
          matched[j] = i
          matchFound = True
          break
    if not matchFound:
      good = False
      break
  if good:
    res += 1
print res
