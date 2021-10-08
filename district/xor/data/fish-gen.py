import random
import re
import string
import sys

def fish(txt):
    txt = re.sub("[A-Z][a-z]+", "Fisk", txt)
    txt = re.sub(" [a-z]+", " fisk", txt)
    return txt

def az(txt):
    ntxt = []
    for i in txt:
        if i in string.ascii_lowercase or i == ' ':
            ntxt.append(i)
    return ''.join(ntxt)

def flagpole(txt):
    mid = random.randint(0, len(txt))
    a = txt[:mid]
    b = txt[mid:]
    return a + " flaggstangsknoppspoleringsmedel " + b

def encode(txt, key):
    ntxt = []
    for i, el in enumerate(txt):
        ntxt.append(ord(el) ^ key[i % len(key)])
    return ntxt

def hexa(txt):
    ans = ""
    for i in txt:
        i = hex(i)[2:]
        if len(i) < 2: i = "0" + i
        ans += i
    return ans

random.seed(int(sys.argv[4]))

path = "texts/" + sys.argv[1]

keylen = int(sys.argv[2])

space = [i for i in range(256)]
key = [random.choice(space) for i in range(keylen)]
# key = [ord(x) for x in "fisk"]

transform = sys.argv[3]

f = open(path, "r").read()

if transform == 'fisk': f = fish(f)
if transform == 'az': f = az(f)
if transform == 'flagpole': f = flagpole(f)

f = encode(f, key)

f = hexa(f)

print(f)
