#!/bin/bash
./visualize < $1 > /tmp/vis.pbm
gm convert /tmp/vis.pbm $1.png
open $1.png
