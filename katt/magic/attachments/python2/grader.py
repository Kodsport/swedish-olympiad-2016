import grader
import magic
import sys

_tricks = []
def _grader_init():
    N, K = map(int, sys.stdin.readline().split())
    L = list(map(int, sys.stdin.readline().split()))
    R = list(map(int, sys.stdin.readline().split()))
    res = magic.magic_score(N, K, L, R)
    if len(_tricks) != N:
        print("error: tried to perform {} tricks, should perform {}".format(len(_tricks)), N)
    else:
        print(res)
        print(" ".join(map(str, _tricks)))

def trick(ans):
    _tricks.append(ans)

if __name__ != "__main__":
    grader._grader_init()
