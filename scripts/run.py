import os
import shlex, subprocess

#list_n = [1000, 5000, 10000]
list_n = [10000]
list_p = [4, 8]
list_t = [4, 8]

open('tempos.txt', 'w').close()

for n in list_n:
    os.environ["OMPI_MATRIX_FILE"] = 'input/' + str(n) + '/matriz.txt'
    os.environ["OMPI_VECTOR_FILE"] = 'input/' + str(n) + '/vetor.txt'

    for p in list_p:
        for t in list_t:    
            if p == 4 and t == 4:
                continue
                
            path = 'output/' + str(n) + '/NP=' + str(p) + '_NT=' + str(t)

            try:
                os.makedirs(path)
            except OSError:
                pass  

            os.environ["OMPI_RESULT_FILE"] = path + '/resultado.txt'
            os.environ["OMP_NUM_THREADS"] = str(t)

            cmd = 'time -f %e -a -o tempos.txt mpirun -np '+ str(p)+' -hostfile hosts ./bin/gauss_jordan'
            args = cmd.split()

            print(os.environ["OMPI_MATRIX_FILE"])
            print(os.environ["OMPI_VECTOR_FILE"])
            print(os.environ["OMPI_RESULT_FILE"])
            print(os.environ["OMP_NUM_THREADS"])
            print(cmd)
            print()

            #for i in range(5):
            PIPE = subprocess.PIPE
            proc = subprocess.Popen(args, stdout=PIPE, stderr=PIPE)
            out, err = proc.communicate()
            errcode = proc.returncode

            if errcode != 0:
                print("ERRO : n={} p={} t={}\n".format(n, p, t))
                print(out)
                print(errcode)
                print('\n')