import re
import sys

# Make sure the input is an integer <=10^20
int_regex = "^(0|[1-9][0-9]*)$"
line = sys.stdin.readline();
assert re.match(int_regex, line)
N = int(line)
assert N <= 10**20

# Make sure solution requires <=100 steps
def digitSum(N):
	return sum(map(int, str(N)))

ans = N + 1
while digitSum(ans) != digitSum(N):
	if ans - N > 100:
		sys.exit(1)
	ans += 1

# Make sure there's no more input 
line = sys.stdin.readline()
assert len(line) == 0	
