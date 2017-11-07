#!/usr/bin/env python3

import os
import sys

if len(sys.argv) > 1:
    until_which = int(sys.argv[1])
else:
    until_which = None

# Os 3 primeiros pra ser mais facil de testar
dims = [10, 20, 40, 1000, 5000, 10000]
dims = dims[:until_which]


for n in dims:
    print('Creating size', n)
    path = 'input/' + str(n)
    try:
        os.makedirs(path)
    except OSError:
        pass

    with open(path + '/matriz.txt', 'w') as matfile:
        for i in range(n*n):
            end = ' '
            if (i + 1) % n == 0:
                end = '\n'

            print(i, file=matfile, end=end)

    with open(path + '/vetor.txt', 'w') as vecfile:
        for i in range(n):
            print(i, file=vecfile)
