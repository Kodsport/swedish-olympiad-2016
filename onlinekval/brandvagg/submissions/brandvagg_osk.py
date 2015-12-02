import sys

N = int(sys.stdin.readline())
rules = []
last = []
cnts = {}

for i in xrange(N):
    rule = sys.stdin.readline().strip().split(" ")
    reqs = []
    command = rule[0]
    for r in rule[1:]:
        left, right = r.split("=")
        reqs.append((left,right))
    rules.append((command,reqs))

P = int(sys.stdin.readline())
for i in xrange(P):
    line = sys.stdin.readline().strip()
    ip, port = line.split(":")
    if len(last) == 1000:
        popped = last.pop(0)
        cnts[popped] -= 1
    if ip not in cnts:
        cnts[ip] = 0
    cnts[ip] += 1 
    last.append(ip)
    for rule in rules:
        ok = True
        subrules = rule[1]
        for subrule in subrules:
            if subrule[0] == "ip":
                if ip != subrule[1]: ok = False
            elif subrule[0] == "port":
                if port != subrule[1]: ok = False
            elif subrule[0] == "limit":
                if cnts[ip] < int(subrule[1]): ok = False
        if ok: # issue command
            cmd = rule[0]
            if cmd == "accept":
                print "accept", i+1
                break
            elif cmd == "drop":
                print "drop", i+1
                break
            elif cmd == "log":
                print "log", i+1
