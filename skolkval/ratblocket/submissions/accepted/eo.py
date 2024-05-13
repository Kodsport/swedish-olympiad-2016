#!/usr/bin/python3
from collections import deque

WALL = "#"
START = "A"
GOAL = "B"
FREE = "."
SWITCH = "c"

STANDING = 0
HORIZONTAL = 1
VERTICAL = 2
UP = 0
RIGHT = 1
DOWN = 2
LEFT = 3

d = [[None]*4 for i in range(3)]
d[STANDING][UP] = [-2, 0, VERTICAL]
d[STANDING][RIGHT] = [0, 1, HORIZONTAL]
d[STANDING][DOWN] = [1, 0, VERTICAL]
d[STANDING][LEFT] = [0, -2, HORIZONTAL]

d[HORIZONTAL][UP] = [-1, 0, HORIZONTAL]
d[HORIZONTAL][RIGHT] = [0, 2, STANDING]
d[HORIZONTAL][DOWN] = [1, 0, HORIZONTAL]
d[HORIZONTAL][LEFT] = [0, -1, STANDING]

d[VERTICAL][UP] = [-1, 0, STANDING]
d[VERTICAL][RIGHT] = [0, 1, VERTICAL]
d[VERTICAL][DOWN] = [2, 0, STANDING]
d[VERTICAL][LEFT] = [0, -1, VERTICAL]

def isFree(grid, r, c, s, m):
  def isCellFree(grid, r, c, m):
    return r >= 0 and r < len(grid) and c >= 0 and c < len(grid[0]) and grid[r][c] != WALL and (not grid[r][c].isdigit() or int(grid[r][c]) == m)

  if s == STANDING:
    return isCellFree(grid, r, c, m)
  elif s == HORIZONTAL:
    return isCellFree(grid, r, c, m) and isCellFree(grid, r, c + 1, m)
  else:
    return isCellFree(grid, r, c, m) and isCellFree(grid, r + 1, c, m)

def bfs(grid):
  sr,sc,gr,gc = -1,-1,-1,-1
  for r in range(len(grid)):
    for c in range(len(grid[r])):
      if grid[r][c] == START:
        sr,sc = r,c
      elif grid[r][c] == GOAL:
        gr,gc = r,c
  dist = [[[[-1]*2 for i in range(3)] for cell in row] for row in grid]
  q = deque()
  q.append((sr,sc,STANDING,0))
  dist[sr][sc][STANDING][0] = 0
  while q:
    r,c,s,m = q.popleft()
    for k in range(4):
      nr = r + d[s][k][0]
      nc = c + d[s][k][1]
      ns = d[s][k][2]
      if isFree(grid, nr, nc, ns, m):
        nm = m ^ (1 if ns == STANDING and grid[nr][nc] == SWITCH else 0)
        if dist[nr][nc][ns][nm] == -1:
          q.append((nr,nc,ns,nm))
          dist[nr][nc][ns][nm] = dist[r][c][s][m] + 1
  a,b = dist[gr][gc][STANDING]
  return a if b == -1 else b if a == -1 else min(a,b)

height, width = map(int, input().split())
grid = [input() for i in range(height)]
print(bfs(grid))
