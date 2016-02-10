#!/usr/bin/env python2
import grader

def init(n):
    ar = [False] * n
    grader.guess(ar)
    ar[0] = ar[1] = ar[2] = True
    grader.guess(ar)
