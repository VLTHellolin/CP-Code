from random import randint
from math import gcd
from time import process_time
from sys import stdin, stdout

LIMIT = 0.2
T = int(stdin.readline())
for t in range(T):
    a, b, c = map(int, stdin.readline().split())
    x = process_time()
    fd = False
    while process_time() - x < LIMIT:
        n = randint(0, 2000)
        if gcd(a * n + b, c) == 1:
            stdout.write('{}\n'.format(n))
            fd = True
            break
    if not fd:
        stdout.write('-1\n')
