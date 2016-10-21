#!/usr/bin/env python

import sys

if "ignore" in sys.argv:
    print "AC 0"
else:
    total_score = 0
    first_error = None
    for line in sys.stdin.readlines():
        verdict, score = line.split()
        total_score += float(score)
        if verdict != "AC" and not first_error:
            first_error = verdict
    if total_score == 0 and first_error:
        print "%s 0" % first_error
    else:
        print "AC %f" % total_score
