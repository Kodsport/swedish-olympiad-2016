#!/usr/bin/env python3

# usage: ./tester.py input_file correct_output < contestants_output

import sys
import re

def die(msg):
  print(msg)
  sys.exit(43)

def accept():
  sys.exit(42)

wanted = open(sys.argv[1],'r').read()
wanted = int(wanted) if wanted else 0

nargs = {
    '---': 0,
    'storlek': 0,
    'pop_first': 0,
    'add_first': 1,
    'pop_back': 0,
    'add_back': 1,
    'add': 2,
    'remove': 1,
    'clear': 0,
}

broken_len = None
was_nonempty = None
was_touched = None
li = None
success = False

def yes():
    global success
    success = True

def process_method(method, args):
    global li
    global broken_len
    global was_nonempty
    global was_touched
    if wanted == 1 and method == "storlek" and broken_len:
        yes()
    if wanted == 2 and method == "remove" and args[0] == len(li) and li:
        yes()
    if wanted == 3 and method == "storlek" and 0 in li:
        yes()
    if wanted == 4 and method == "add" and args[1] == 0 and li:
        yes()
    if wanted == 5 and method == "pop_first" and not li and not was_nonempty:
        yes()
    if wanted == 6 and method == "add_back" and not li and was_nonempty:
        yes()
    if wanted == 7 and method == "add_first" and not li and not was_nonempty:
        yes()
    if wanted == 8 and method == "add" and args[1] == 0 and not was_touched:
        yes()
    if wanted == 9 and method == "add" and args[1] < 0:
        yes()
    if wanted == 10 and method == "pop_back" and li:
        yes()

    if method == "---":
        broken_len = False
        was_nonempty = False
        was_touched = False
        li = []
    elif method == "clear":
        if li:
            broken_len = True
        was_nonempty = False
        was_touched = True
        li = []
    elif method == "storlek":
        pass
    elif method == "pop_first":
        if li:
            li = li[1:]
            was_touched = True
    elif method == "pop_back":
        if li:
            li.pop()
            was_touched = True
    elif method == "add_first":
        li[0:0] = args
        was_nonempty = True
        was_touched = True
    elif method == "add_back":
        li.append(args[0])
        was_nonempty = True
        was_touched = True
    elif method == "add":
        if 0 <= args[1] <= len(li):
            li.insert(args[1], args[0])
            was_nonempty = True
            was_touched = True
    elif method == "remove":
        if 0 <= args[0] < len(li):
            del li[args[0]]
            was_touched = True
    else:
        assert False

process_method("---", [])

try:
    count = 0
    for x in sys.stdin:
        count += 1
        if count > 1000:
            die("too many lines")
        parts = x.strip().split(' ')
        method = parts[0] if parts else ''
        if method not in nargs:
            die("unknown method {}".format(method))
        args = parts[1:]
        if nargs[method] != len(args):
            die("wrong number of args to {}".format(method))
        args = list(map(int, args))
        if method.startswith('add') and abs(args[0]) > 1000:
            die("out of range")
        process_method(method, args)
except ValueError:
    die("unparsable")

if success or wanted == 0:
    accept()
else:
    die("didn't trigger edge case")

