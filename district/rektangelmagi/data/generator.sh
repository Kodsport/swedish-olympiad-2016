#!/usr/bin/env bash
. ../../../testdata_tools/gen.sh

use_solution misof.cc

testcases() {
  local DIRECTORY=$1

  if [ ! -d "$DIRECTORY" ]; then
    echo "Error: $DIRECTORY is not a valid directory."
    return 1
  fi

  local found=false
  for file in "$DIRECTORY"/*.in; do
    if [ ! -e "$file" ]; then
      continue
    fi
    found=true
    tc_manual "$(realpath --relative-to="$PWD" "$file")"
  done

  if [ "$found" = false ]; then
    echo "No .in files found in $DIRECTORY"
  fi
}

# Generate answers to sample cases
samplegroup
sample 1
sample 2
sample 3
sample 4


group 01_complete 10
# limits R=6 C=6 complete=true
testcases ../manual-tests/g01

group 02_1RorC 10
# limits R=6 C=6
testcases ../manual-tests/g02
tc 2

group 03_RCis2 10
# limits R=6 C=6 r=2 c=2
testcases ../manual-tests/g03

group 04_uniqueWithEasyStrat 10
# limits R=6 C=6
include_group 01_complete
testcases ../manual-tests/g04
tc 3

group 05_uniqueWithInts 10
# limits R=6 C=6 unique=true ints=true
testcases ../manual-tests/g05
tc 1

group 06_unique 10
# limits R=6 C=6 unique=true
include_group 04_uniqueWithEasyStrat
include_group 05_uniqueWithInts
testcases ../manual-tests/g06

group 07_uniqueWithIntsOrNoSol 10
# limits R=6 C=6
include_group 05_uniqueWithInts
testcases ../manual-tests/g07


group 08_uniqueOrNoSol 10
# limits R=6 C=6
include_group 06_unique
include_group 07_uniqueWithIntsOrNoSol
testcases ../manual-tests/g08

group 09_allPrev 10
# limits R=6 C=6
include_group 02_1RorC
include_group 03_RCis2
include_group 08_uniqueOrNoSol
testcases ../manual-tests/g09
tc 4

group 10_all 10
# limits R=50 C=50
include_group 09_allPrev
testcases ../manual-tests/g10