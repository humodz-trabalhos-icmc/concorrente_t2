#!/usr/bin/env python3

import os


dims = [1000, 5000, 10000]


for n in dims:
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

            print(i, file=matfile, end='')

    with open(path + '/vetor.txt', 'w') as vecfile:
        for i in range(n):
            print(i, file=vecfile)
