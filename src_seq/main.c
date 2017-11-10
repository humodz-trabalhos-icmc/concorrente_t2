#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "gauss.h"

double **criar_matriz(int tamanho) {
	double **matriz = (double**) malloc(sizeof(double*)*tamanho);
	int i;
	
	for(i=0;i<tamanho;i++)
		matriz[i] = (double*) malloc(sizeof(double)*tamanho);

	return matriz;
}

int main(int argc, char **argv) {
	int i,j,tamanho;
	double **matriz = NULL; //matriz de numeros
	double *vetor = NULL; //vetor para concatenar com a matriz
	const char *tamanho_, *path_mat, *path_vet, *path_out;
	FILE *file = NULL;
	
	tamanho_ = getenv("GJ_SIZE");
	path_mat = getenv("GJ_PATH_MAT");
	path_vet = getenv("GJ_PATH_VET");
	path_out = getenv("GJ_PATH_OUT");
	
	tamanho = atoi(tamanho_);
	vetor = (double*) malloc(sizeof(double)*tamanho);
	matriz = criar_matriz(tamanho);	
	
	file = fopen(path_mat, "r");
	assert(file != NULL);

	for(i=0; i<tamanho; i++) {
		for(j=0;j<tamanho;j++) {
			assert(!feof(file));
			fscanf(file, " %lf", &matriz[i][j]);
		}
	}
	fclose(file);

	file = fopen(path_vet, "r");
	assert(file != NULL);

	for(i=0; i<tamanho; i++) {
		fscanf(file, " %lf", &vetor[i]);
	}
	fclose(file);

	//realloca memoria para matriz junto com a identidade
	for(i=0;i<tamanho;i++) {
		matriz[i] = (double*) realloc(matriz[i],sizeof(double)*(tamanho+1));
		matriz[i][tamanho] = vetor[i];
	}

	gauss_jordan(matriz,tamanho,tamanho+1);

	file = fopen(path_out, "w");
	assert(file != NULL);
	
	for(i=0; i<tamanho; i++) {
		fprintf(file, "%.5lf\n", matriz[i][tamanho]);
	}
	fclose(file);

	//libera memoria
	for(i=0;i<tamanho;i++) {
		free(matriz[i]);
	}
	free(matriz);

	return 0;
}
