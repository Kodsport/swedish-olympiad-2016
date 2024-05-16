#!/bin/bash
PPATH=$(realpath ..)
. ../../../testdata_tools/gen.sh

ulimit -s unlimited

use_solution vvvvvv_ema.cpp

samplegroup
sample v1
sample v2
sample v3


group group1 20
tc_manual ../manual_data/v1_1.in
tc_manual ../manual_data/v1_2.in
tc_manual ../manual_data/v1_3.in
tc_manual ../manual_data/v1_4.in
tc_manual ../manual_data/v1_5.in

group group2 15
tc_manual ../manual_data/v2_1.in
tc_manual ../manual_data/v2_2.in
tc_manual ../manual_data/v2_3.in
tc_manual ../manual_data/v2_4.in
tc_manual ../manual_data/v2_5.in

group group3 15
include_group group1
include_group group2
tc_manual ../manual_data/v3_1.in
tc_manual ../manual_data/v3_2.in
tc_manual ../manual_data/v3_3.in
tc_manual ../manual_data/v3_4.in
tc_manual ../manual_data/v3_5.in

group group4 20
tc_manual ../manual_data/v4_1.in
tc_manual ../manual_data/v4_2.in
tc_manual ../manual_data/v4_3.in
tc_manual ../manual_data/v4_4.in
tc_manual ../manual_data/v4_5.in

group group5 30
include_group sample
include_group group3
include_group group4
tc_manual ../manual_data/v5_1.in
tc_manual ../manual_data/v5_2.in
tc_manual ../manual_data/v5_3.in
tc_manual ../manual_data/v5_4.in
tc_manual ../manual_data/v5_5.in
