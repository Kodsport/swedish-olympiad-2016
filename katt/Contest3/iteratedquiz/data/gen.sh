#!/bin/bash
. ../../../../testdata_tools/gen.sh


ulimit -s unlimited
use_solution ../dummy.cpp

compile printer.py


group g1 9
tc g1-1 printer 10 exp 9

group g2 11
tc g2-1 printer 1000 2n 11

group g3 15
tc g3-1 printer 1000 n 15

group g4 65
tc g4-1 printer 1000 rel 65
tc g4-2 printer 1000 rel 65
tc g4-3 printer 1000 rel 65
tc g4-4 printer 1000 rel 65
tc g4-5 printer 1000 rel 65
tc g4-6 printer 1000 rel 65
tc g4-7 printer 1000 rel 65
tc g4-8 printer 1000 rel 65
tc g4-9 printer 1000 rel 65
tc g4-10 printer 1000 rel 65
