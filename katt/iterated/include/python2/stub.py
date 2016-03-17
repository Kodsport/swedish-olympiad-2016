import stub
import iterated
import sys
import os

N = -1
def _grader_init():
    global N
    global inf
    global outf
    inf = os.fdopen(os.open(sys.argv[1], os.O_RDONLY))
    outf = open(sys.argv[2], "w+")
    N = int(inf.readline())
    iterated.init(N)

def guess(ans):
    assert len(ans) == N
    assert all(x == True or x == False for x in ans)
    s = ''.join('1' if x else '0' for x in ans)
    outf.write(s)
    outf.write("\n")
    outf.flush()
    res = int(inf.readline())
    if res == N:
        sys.exit(0)
    return res

if __name__ != "__main__":
    stub._grader_init()
