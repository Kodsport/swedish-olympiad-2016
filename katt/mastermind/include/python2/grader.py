import mastermind
import grader
import sys

N = -1
def _grader_init():
    global N
    N = int(sys.stdin.readline())
    mastermind.init(N)

def guess(ans):
    assert len(ans) == N
    assert all(x == True or x == False for x in ans)
    s = ''.join('1' if x else '0' for x in ans)
    print(s)
    sys.stdout.flush()
    res = int(sys.stdin.readline())
    if res == N:
        sys.exit(0)
    return res

if __name__ != "__main__":
    grader._grader_init()
