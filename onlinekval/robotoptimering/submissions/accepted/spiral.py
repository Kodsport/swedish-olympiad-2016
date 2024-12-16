#!/usr/bin/env python3
# We don't commit the rest of the solutions as to not spoil them
# But they do exist
ans = {
#robot_spiral
'robot_spiral': """
main:
    for 1000 {
        forward
    }
    left
    call main
"""
}
casename = input()
print (ans[casename])