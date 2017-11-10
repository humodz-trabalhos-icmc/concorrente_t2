import os
import shlex, subprocess

list_n = [1000, 5000, 10000]

open('tempos_seq.txt', 'w').close()

for n in list_n:
    os.environ["GJ_SIZE"]     = str(n)
    os.environ["GJ_PATH_MAT"] = 'input/'  + str(n) + '/matriz.txt'
    os.environ["GJ_PATH_VET"] = 'input/'  + str(n) + '/vetor.txt'
    
    path = 'output/' + str(n) + '/SEQ'
    try:
        os.makedirs(path)
    except OSError:
        pass
    
    os.environ["GJ_PATH_OUT"] = path+'/resultado.txt'
    cmd = 'time -f %e -a -o tempos_seq.txt ./bin/gauss_jordan-seq'
    args = cmd.split()
    
    print(os.environ["GJ_SIZE"])
    print(os.environ["GJ_PATH_MAT"])
    print(os.environ["GJ_PATH_VET"])
    print(os.environ["GJ_PATH_OUT"])
    print(cmd)
    print()    
    
    for i in range(5):                
        PIPE = subprocess.PIPE
        proc = subprocess.Popen(args, stdout=PIPE, stderr=PIPE)
        out, err = proc.communicate()
        errcode = proc.returncode
        
        if errcode != 0:
            print("n={} p={} t={}".format(n, p, t))
            print(out)
            print(errcode)
            print()