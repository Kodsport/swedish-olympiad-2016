#!/bin/bash
for acc in submissions/*.cpp; do
	set -e
	g++ -O2 -std=c++11 $acc -g -D_GLIBCXX_DEBUG -o /tmp/solnedgang_ac
	set +e
	echo "Testing $acc"
	for a in data/secret/*/*.in; do
		printf "$a: "
		/tmp/solnedgang_ac < $a > /tmp/solnedgang_tmp.ans &
		code=$!
		isDone="false"
		for i in {0..20}; do
			sleep 0.1
			kill -0 $code 2> /dev/null
			if [ $? -eq 1 ]; then
				isDone="true"
				diff -U8 /tmp/solnedgang_tmp.ans ${a%.in}.ans > /dev/null
				if [ $? -eq 0 ]; then
					printf "AC"
				else
					printf "WA/RTE"
				fi
				rm /tmp/solnedgang_tmp.ans
				break
			fi
		done

		if [ "$isDone" = "false" ]; then
			kill -9 $code 2> /dev/null
			printf "TLE"
		fi
		printf '\n'
	done
done

