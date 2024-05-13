#!/usr/bin/python3
import sys
import random

if len(sys.argv) != 6:
    print("Usage: python gen_testcase.py N P1 P2 MAXL seed")
    print("P1 and P2 are probabilities for two of the colors (randomly decided) in a given interval.")
    exit()

COL = ["RGB","RBG","BGR","BRG","GRB","GBR"]

n = int(sys.argv[1])
P1 = float(sys.argv[2])
P2 = float(sys.argv[3])
MAXL = int(sys.argv[4])
seed = int(sys.argv[5])
random.seed(seed)
while True:
    s=""
    for i in range(n):
       col=COL[random.randint(0,5)]
       used=set()
       while(len(used)<3):
           r=random.random()
           if(r<P1):
               s+=col[0]
           elif(r<P1+P2):
               s+=col[1]
           else:
               s+=col[2]
           used.add(s[-1])
    s+="".join([COL[0][random.randint(0,2)] for i in range(random.randint(0,10))])   #Add some random tail
    if(len(s)<=MAXL):
        print(n)
        print(s)
        break
