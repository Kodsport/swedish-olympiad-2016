#!/bin/bash
for acc in submissions/*/*.cpp; do
	set -e
	g++ -O2 -std=c++11 $acc -o /tmp/solnedgang_ac
	set +e
	echo "Testing $acc"
	for a in data/secret/*/*.in; do
		printf "$a: "
		/tmp/solnedgang_ac < $a > /tmp/solnedgang_tmp.ans &
		code=$!
		isDone="false"
		sleep 0.02
		for i in {0..50}; do
			kill -0 $code 2> /dev/null
			if [ $? -eq 1 ]; then
				isDone="true"
				if [ $s /tmp/solnedgang_tmp.ans ]; then
					diff -U8 /tmp/solnedgang_tmp.ans ${a%.in}.ans > /dev/null
					if [ $? -eq 0 ]; then
						printf "AC"
					else
						printf "WA"
					fi
				else
					printf "RTE (no output)"
				fi

				rm /tmp/solnedgang_tmp.ans
				break
			fi
			sleep 0.1
		done

		if [ "$isDone" = "false" ]; then
			kill -9 $code 2> /dev/null
			printf "TLE"
		fi
		printf '\n'
	done
done

