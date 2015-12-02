#!/bin/bash
for i in "$@"
do
	./visualize < $i > /tmp/vis.pbm
	gm convert -sample 1000% /tmp/vis.pbm $i.png
	open $i.png
done
