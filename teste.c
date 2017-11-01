#include <stdlib.h>
#include <stdio.h>
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
	
	printf("entre com o grau da matriz\n");
	scanf("%d",&tamanho);
	vetor = (double*) malloc(sizeof(double)*tamanho);
	matriz = criar_matriz(tamanho);	

	printf("entre com a matriz\n");
	for(i=0; i<tamanho; i++)
		for(j=0;j<tamanho;j++)
			scanf("%lf",&matriz[i][j]);

	printf("vetor para concatenar com a matriz\n");
	for(i=0; i<tamanho; i++)	
		scanf("%lf",&vetor[i]);

	//realloca memoria para matriz junto com a identidade
	for(i=0;i<tamanho;i++) {
		matriz[i] = (double*) realloc(matriz[i],sizeof(double)*(tamanho+1));
		matriz[i][tamanho] = vetor[i];
	}

	for(i=0; i<tamanho; i++) {
		for(j=0;j<=tamanho;j++)
			printf("%.2lf ",matriz[i][j]);
		printf("\n");
	}

	printf("\n");

	gauss_jordan(matriz,tamanho,tamanho+1);

	for(i=0; i<tamanho; i++) {
		for(j=0;j<=tamanho;j++)
			printf("%.2lf ",matriz[i][j]);
		printf("\n");
	}

	//libera memoria
	for(i=0;i<tamanho;i++) {
		free(matriz[i]);
	}
	free(matriz);

	return 0;
}
