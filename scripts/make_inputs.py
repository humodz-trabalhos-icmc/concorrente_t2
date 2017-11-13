import numpy as np
import sys
import os

#assert len(sys.argv) > 1
#N = int(sys.argv[1])
for N in [8, 10, 20, 40, 1000, 5000, 10000]:
    path = '../input/' + str(N)
    
    try:
        os.makedirs(path)
    except OSError:
        pass
    
    v = np.random.randint(0, 10, (N, 1))
    M = v.T * v + np.identity(N)

    np.savetxt(path + '/matriz.txt', M, fmt='%0.f')
    np.savetxt(path + '/vetor.txt', v+1, fmt='%0.f')