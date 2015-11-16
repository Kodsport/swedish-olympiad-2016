from collections import deque

WALL = "#"
START = "S"
GOAL = "G"
FREE = "."

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

def isFree(grid, r, c, s):
  def isCellFree(grid, r, c):
    return r >= 0 and r < len(grid) and c >= 0 and c < len(grid[0]) and grid[r][c] != WALL

  if s == STANDING:
    return isCellFree(grid, r, c)
  elif s == HORIZONTAL:
    return isCellFree(grid, r, c) and isCellFree(grid, r, c + 1)
  else:
    return isCellFree(grid, r, c) and isCellFree(grid, r + 1, c)

def bfs(grid):
  sr,sc,gr,gc = -1,-1,-1,-1
  for r in range(len(grid)):
    for c in range(len(grid[r])):
      if grid[r][c] == START:
        sr,sc = r,c
      elif grid[r][c] == GOAL:
        gr,gc = r,c
  dist = [[[-1]*3 for cell in row] for row in grid]
  q = deque()
  q.append((sr,sc,STANDING))
  dist[sr][sc][STANDING] = 0
  while q:
    r,c,s = q.popleft()
    for k in range(4):
      nr = r + d[s][k][0]
      nc = c + d[s][k][1]
      ns = d[s][k][2]
      if isFree(grid, nr, nc, ns) and dist[nr][nc][ns] == -1:
        q.append((nr,nc,ns))
        dist[nr][nc][ns] = dist[r][c][s] + 1
  return dist[gr][gc][STANDING]

width, height = map(int, raw_input().split())
grid = [raw_input() for i in range(height)]
print bfs(grid)
