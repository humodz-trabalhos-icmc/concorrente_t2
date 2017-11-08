#!/usr/bin/env python3

import os
import sys

if len(sys.argv) > 1:
    until_which = int(sys.argv[1])
else:
    until_which = 4

# Os 3 primeiros pra ser mais facil de testar
dims = [8, 10, 20, 40, 1000, 5000, 10000, 0]
dims = dims[:until_which]


for n in dims:
    print('Creating size', n)
    path = 'input/' + str(n)
    try:
        os.makedirs(path)
    except OSError:
        pass

    with open(path + '/matriz.txt', 'w') as matfile:
        for i in range(n):
            for j in range(n):
                # print(i*n+j, file=matfile, end=' ')
                print(j*n+i, file=matfile, end=' ')
            print('', file=matfile)

    with open(path + '/vetor.txt', 'w') as vecfile:
        for i in range(n):
            print(i+1, file=vecfile)
