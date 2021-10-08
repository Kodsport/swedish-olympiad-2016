#!/usr/bin/env python3
import sys
sys.stdout.write("""\
add_back 10
clear
storlek
---
add_back 1
remove 1
---
add_back 0
storlek
---
add_first 5
add 4 0
---
pop_first
---
add_back 5
pop_first
add_back 5
---
add_first 5
---
add 10 0
---
add 10 -1
---
add_back 5
pop_back
""")
