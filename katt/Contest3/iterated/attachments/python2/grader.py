import iterated
import grader
import sys

N = -1
guesses = 0
target = None
def _grader_init():
    global N
    global target
    N = int(sys.stdin.readline())
    inp = sys.stdin.readline().strip()
    if len(inp) != N:
        print "Invalid input string."
        sys.exit(2)
    if any(x != '0' and x != '1' for x in inp):
        print "Invalid input string."
        sys.exit(2)
    target = [True if x == '1' else False for x in inp]
    mastermind.init(N)
    print "Failure."
    sys.exit(1)

def guess(ans):
    assert len(ans) == N
    assert all(x == True or x == False for x in ans)
    global guesses
    guesses += 1
    res = 0
    for i in range(N):
        res += 1 if ans[i] == target[i] else 0
    if res == N:
        print "Success, took", guesses, "guesses."
        sys.exit(0)
    return res

if __name__ == "__main__":
    grader._grader_init()
