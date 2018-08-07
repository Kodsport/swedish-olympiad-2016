#!/usr/bin/env python3

ans = {
'robot_concentric': """main:
for 13 { forward }
left
for 100 { forward }
right
for 4 {
for 100 { forward }
}
""",'robot_cross': """main:
for 13 { forward }
left
for 100 { forward }
right
for 4 {
for 100 { forward }
}
""",'robot_diagonal': """main:
for 13 { forward }
left
for 100 { forward }
right
for 4 {
for 100 { forward }
}
""",'robot_ew_manuell': """main:
for 13 { forward }
left
for 100 { forward }
right
for 4 {
for 100 { forward }
}
""",'robot_path_freedom': """main:
for 13 { forward }
left
for 100 { forward }
right
for 4 {
for 100 { forward }
}
""",'robot_path_freedom2': """main:
for 13 { forward }
left
for 100 { forward }
right
for 4 {
for 100 { forward }
}
""",'robot_rand_60': """main:
for 13 { forward }
left
for 100 { forward }
right
for 4 {
for 100 { forward }
}
""",'robot_rand_80': """main:
for 13 { forward }
left
for 100 { forward }
right
for 4 {
for 100 { forward }
}
""",'robot_maze': """main:
for 13 { forward }
left
for 100 { forward }
right
for 4 {
for 100 { forward }
}
""",'robot_spiral': """main:
for 13 { forward }
left
for 100 { forward }
right
for 4 {
for 100 { forward }
}
""",}
casename = input()
print (ans[casename])
