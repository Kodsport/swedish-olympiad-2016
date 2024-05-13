#!/bin/bash
#!/bin/bash
. ../../../testdata_tools/gen.sh

use_solution fargrobot.py

compile gen_rand.py

samplegroup
sample sample01
sample sample02
sample sample03
sample sample04

group g1 20
tc_manual 1

group g2 30
include_group g1
tc sample01
tc sample02
tc sample03
tc sample04
tc g2-1 gen_rand 1 0.33 0.33 10 
tc g2-2 gen_rand 1 0.01 0.02 100 
tc g2-3 gen_rand 2 0.33 0.33 50 
tc g2-4 gen_rand 2 0.02 0.45 100 
tc g2-5 gen_rand 3 0.33 0.33 50 
tc g2-6 gen_rand 3 0.10 0.50 100 
tc g2-7 gen_rand 4 0.33 0.33 50 
tc g2-8 gen_rand 4 0.20 0.30 100 

group g3 20
tc g3-1 gen_rand 5 0.33 0.33 100
tc g3-2 gen_rand 7 0.05 0.40 200
tc g3-3 gen_rand 10 0.33 0.33 100
tc g3-4 gen_rand 10 0.20 0.20 200
tc g3-5 gen_rand 10 0.10 0.45 200
tc g3-6 gen_rand 10 0.08 0.20 200

group g4 30
tc g4-1 gen_rand 20 0.33 0.33 200
tc g4-2 gen_rand 20 0.10 0.45 200
tc g4-3 gen_rand 25 0.33 0.33 200
tc g4-4 gen_rand 25 0.20 0.20 200
tc g4-5 gen_rand 25 0.10 0.40 200

