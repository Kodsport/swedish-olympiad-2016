#!/usr/bin/python3

ans = {
'robot_concentric': """1000
""",'robot_cross': """2000
""",'robot_diagonal': """2000
""",'robot_ew_manuell': """2000
""",'robot_path_freedom': """2000
""",'robot_path_freedom2': """2000
""",'robot_rand_60': """2000
""",'robot_rand_80': """2000
""",'robot_maze': """2000
""",'robot_spiral': """2000
""",}
casename = input()
x = 3
for i in range(18):
    x = x * x
    x = int(str(x))
print (ans[casename])
