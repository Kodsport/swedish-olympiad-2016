#!/usr/bin/env python3
#
# Testing tool for the task Iterated Quiz.
#
# Usage:
#
#   python3 testing_tool.py [--silent] program... <input.txt
#
# input.txt uses the following format:
#
# N
# S
# 
# Where N is the number of questions, and S is a string consisting of 0/1's,
# describing whether each question is "yes" or "no"
#
# For example, if you have a Python solution that you would run using
# "python3 file.py", you could invoke the testing tool with:
#
#   python3 testing_tool.py python3 file.py < input.txt
#
# where input.txt is a file that contains e.g.
#
# 5
# 11010
#
# If --silent is passed, the communication output will not be printed.
#
# The tool is provided as-is, and you should feel free to make
# whatever alterations or augmentations you like to it.
#

import subprocess
import sys

def error(msg):
    print("ERROR:", msg)
    sys.exit(1)

def main():
    silent = False
    args = sys.argv[1:]
    if args and args[0] == "--silent":
        args = args[1:]
        silent = True
    if not args or args == ["--help"] or args == ["-h"]:
        print("Usage:", sys.argv[0], "[--silent] program... <input.txt")
        sys.exit(0)
    
    try:
        n = int(input())
    except Exception:
        error("bad input format: failed to parse first line as integer")
    try:
        s = input()
    except Exception:
        error(f"bad input format: failed to parse second line as string")
    assert len(s)==n, f"len(s)={len(s)}, which is different from {n=}"
    assert all(c in ('0', '1') for c in s), "c does not entirely consist of 0 or 1"
                
    proc = subprocess.Popen(args, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
    if not silent:
        print(f"[*] Running with N = {n}, S = {s}")

    proc.stdin.write(f"{n}\n".encode("utf8"))
    proc.stdin.flush()

    proc.stdin.flush()
    if not silent:
        print(f"< {n}")

    queries = 0

    while True:
        query = proc.stdout.readline().decode("utf8")
        query = query.strip()

        if not silent:
            print(f"> {query}")

        queries += 1

        if query==s:
            print(f"[*] OK: correctly answered all questions. queries used: {queries}.")
            exit(0)

        assert len(query)==n, f"len(query)={len(query)}, which is different from {n=}"
        assert all(c in ('0', '1') for c in query), f"query does not entirely consist of 0 or 1, {query}"
    
        num_correct = 0
        for i in range(n):
            num_correct += query[i]==s[i]

        proc.stdin.write(f"{num_correct}\n".encode("utf8"))
        proc.stdin.flush()
        if not silent:
            print("<",num_correct)
        

if __name__ == "__main__":
    main()