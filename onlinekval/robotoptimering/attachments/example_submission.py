#!/usr/bin/env python3
ans = {
#robot_concentric    
'robot_concentric': """
main:
    for 1 {
        for 2 {
            left
            for 3 {
                forward
            }
            gotoblocked main
        }
        right
    }
""",
#robot_cross
'robot_cross': """
forward15:
    for 15 {
        forward
    }
    return

rotate:
    right
    gotoblocked rotate

main:
    for 1000 {
        call forward15
        gotoblocked rotate
    }

""",
#robot_diagonal
'robot_diagonal': """
main:

""",
#robot_ew_manuell
'robot_ew_manuell': """
main:

""",
#robot_path_freedom
'robot_path_freedom': """
main:

""",
#robot_path_freedom2
'robot_path_freedom2': """
main:

""",
#robot_rand_60
'robot_rand_60': """
main:

""",
#robot_rand_80
'robot_rand_80': """
main:

""",
#robot_maze
'robot_maze': """
main:

""",
#robot_spiral
'robot_spiral': """
main:

"""
}
casename = input()
print (ans[casename])
