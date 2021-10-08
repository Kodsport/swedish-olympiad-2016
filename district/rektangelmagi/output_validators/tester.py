#!/usr/bin/python2

# tester for the task "arithmetic"
# usage: ./tester.py input_file correct_output contestants_output
# alternate usage: python tester.py input_file correct_output contestants_output

from sys import stdin, exit, argv
import re

def die(msg):
  print(msg)
  exit(43)

def accept():
  exit(42)

def tofrac(x):
    if '/-' in x:
        x = x.replace('/-', '/')
        if x.startswith('-'):
            x = x[1:]
        else:
            x = '-' + x
    return Fraction(x)

fin, fcor, fhis = open(argv[1],'r'), open(argv[2],'r'), stdin
from fractions import Fraction

correct = fcor.read().strip()
if correct=='ej magisk':
  outputdata = fhis.read().strip()
  if outputdata=='ej magisk': accept()
  else: die("failed to detect that there is no solution")

R, C = [ int(x) for x in fin.readline().split() ]
inputdata = [ x.split() for x in fin.readlines() ]
outputdata = [ x.split() for x in fhis.readlines() ]

if len(outputdata) != R: die("incorrect number of rows")
for x in outputdata:
  if len(x) != C: die("incorrect number of tokens in a row")

allowed = re.compile('-?[0-9]{1,20}(/-?[0-9]{1,20})?$')
for r in range(R):
  for c in range(C):
    if not allowed.match(outputdata[r][c]):
      die("some token is not a properly formatted fraction")

try: foutputdata = [ [ tofrac(x) for x in y ] for y in outputdata ]
except: die("failed to parse some token as a fraction")

for r in range(R):
  for c in range(C):
    if inputdata[r][c] != '.':
      if foutputdata[r][c] != tofrac(inputdata[r][c]):
        die("one of the input values was modified")

def is_arithmetic(seq):
  if len(seq)<=1: return True
  d = seq[1] - seq[0]
  for i in range(2,len(seq)):
    if seq[i] != seq[0] + i * d:
      return False
  return True

for x in foutputdata:
  if not is_arithmetic(x):
    die("some row is not an arithmetic sequence")
for c in range(C):
  if not is_arithmetic( [ x[c] for x in foutputdata ] ):
    die("some column is not an arithmetic sequence")

accept()
