#!/usr/bin/env python
import sys
from Tkinter import *


if len(sys.argv)!=3:
   print "Usage: show.py inputfile  pixelspersquare"
   exit(1)

lines=open(sys.argv[1]).readlines()
mult=int(sys.argv[2])

W=int(lines[0].split()[0])
H=int(lines[0].split()[1])
canvas = Canvas(width=W*mult+10, height=H*mult+10, bg='white')  
canvas.pack(expand=YES, fill=BOTH)

for line in lines[1:]:
    [x1,y1,x2,y2]=[int(x) for x in line.split()]
    canvas.create_line(x1*mult+5, (H-y1)*mult+5, x2*mult+5, (H-y2)*mult+5,width=3)              
raw_input()
