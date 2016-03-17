#!/bin/bash

rm -rf secret/
mkdir secret/

INDEX=0
# Args: N, M, E
function tc {
	python gen.py $1 $2 $3 $INDEX > secret/$INDEX.in
	let INDEX++
}

# let alt = (do n <-[100, 1000]; m <- [2*n, n*floor (sqrt (fromIntegral n)) :: Integer, n*(n-1) `div` 2]; e <- [10, floor (sqrt (fromIntegral m)), m `div` 3]; return [n, m, e])
# mapM_ putStrLn $ map (("tc " ++) . unwords . map show) alt
tc 20 100 20
tc 100 200 10
tc 100 200 66
tc 100 1000 31
tc 100 1000 333
tc 100 4950 10
tc 1000 2000 666
tc 1000 31000 10
tc 1000 31000 10333
tc 1000 499500 706
# tc 100 200 14
# tc 100 1000 10
# tc 100 4950 70
# tc 100 4950 1650
# tc 1000 2000 10
# tc 1000 2000 44
# tc 1000 31000 176
# tc 1000 499500 10
# tc 1000 499500 166500
