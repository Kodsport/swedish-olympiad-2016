import grader

def magic_score(N, K, L, R):
    ds = []
    for i in range(N):
        assert R[i] - L[i] == 2
        ds.append(min(abs(L[i]), abs(R[i])))
        grader.trick(0)
    res = 0
    ds.sort()
    for x in ds:
        if x <= K:
            K -= x
            res += 1
    return res
