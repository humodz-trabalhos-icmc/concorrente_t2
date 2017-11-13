# T2 Concorrente

1 - Compilar:

1.1 - Paralelo
$ make all

1.2 - Sequencial
$ make all_seq

2 - Executar uma matriz

2.1 - Paralelo

2.1.1 - Set de variáveis
$ export OMPI_MATRIX_FILE=input/1000/matriz.txt
$ export OMPI_VECTOR_FILE=input/1000/vetor.txt
$ export OMPI_RESULT_FILE=output/1000/NP=2_NT=4/resultado.txt
$ export OMP_NUM_THREADS=4

2.1.2 - Executar
make run NP=4

2.2 Sequencial

2.2.1 - Set de variáveis
$ export GJ_SIZE=1000
$ export GJ_PATH_MAT=input/1000/matriz.txt
$ export GJ_PATH_VET=input/1000/vetor.txt
$ export GJ_PATH_OUT=output/1000/SEQ/resultado.txt'

2.2.1 - Executar
make run_seq


Para executar os scripts python:

1 - Criar as entradas
$ python3 scripts/make_inputs.py

2 - Rodar paralelo
$ python3 run.py

3 - Rodar sequencial
$ python3 run_seq.py

4 - Plotar gráficos e planilha de estatísticas de execução
$ python3 plot.py


Obs: Para a completa execução do trabalho deve-se compilar, gerar as entradas, rodar run.py, run_seq.py e plot.py.


## Integrantes
* Bruno Henrique Rasteiro 9292910
* Hugo Moraes Dzin 8532186
* Luiz Eduardo Dorici 
* Matheus Gomes da Silva Horta 8532321
