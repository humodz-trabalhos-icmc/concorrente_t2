#ifndef _GAUSS_H__
#define _GAUSS_H__

#include <stdlib.h>
#include <stdio.h>

//Luiz Eduardo Dorici NUSP: 4165850

//trocar linha
void trocar(double **matriz,int l1, int l2) {
	double *vector = matriz[l1];
	matriz[l1] = matriz[l2];
	matriz[l2] = vector;
}

//somar linhas(funcao complementar da multiplicacao)
void somar(double **matriz,double *vector,int linha,int tamanho) {
	int i;

	for(i=0;i<tamanho;i++)
		matriz[linha][i] += vector[i];
}

//multiplica por uma constante
//(caso soma seja 1 entao o valor resultante da multiplicacao eh somando na linha que sera a resultante)
void multiplicar(int soma,double **matriz,int l1,int l2, int tamanho,double constante) {
	int i;
	double *vector = (double*) malloc(sizeof(double)*tamanho);

	//caso soma seja 0 entao apenas eh feita a multiplicacao por uma constante na linha desejada
	if(!soma) {
		for(i=0;i<tamanho;i++)
			matriz[l1][i] *= constante;
	}
	//caso contrario deve-se multiplicar e depois somar na linha desejada para dar o resultado
	//nesse caso usa-se um vetor auxiliar para nao modificar a linha que sera somada para obter o resultado final
	else {
		for(i=0;i<tamanho;i++) {
			vector[i] = matriz[l1][i] * constante;
		}
		somar(matriz,vector,l2,tamanho);
	}
	free(vector);
}

//divide por constante
void divide(double **matriz,int linha,int tamanho,double constante) {
		int i;

		for(i=0;i<tamanho;i++)
			matriz[linha][i] /= constante;
}

//organiza matriz triangular superior para poder encontrar os pivots na diagonal principal
void triangular(double **matriz, int n, int linha, int coluna) {
	int k;
 
			for(k=linha;k<n-linha;k++) {			
				if(matriz[k][coluna] != 0) {
					trocar(matriz,linha,k);
					break;
				}
			}
}

//metodo de gauss-jordan para escalonar a matriz
void gauss_jordan(double **matriz, int linhas, int colunas) {
	int i,j,k;
	double aux;

	//triangular(matriz,linhas);

	for(i=0;i<linhas;i++) {
		for(j=0;j<linhas;j++) {

			//caso o pivot seja maior que 0 entao divide-se toda sua linha por -pivot
			if(i == j && matriz[i][j] != 1) {
				if(i == j && matriz[i][j] == 0)
					//printf("fodeu\n");
					//exit(0);
					//tratar pivoteamento durante o processo de escalonamento
					triangular(matriz,linhas, i, j);
				else
					divide(matriz,i,colunas,matriz[i][j]);
			}

			//caso o pivot seja 1
			if(i == j && matriz[i][j] == 1) {

				//caso diferente de zero, zera as linhas a baixo e a cima do pivot
				for(k=0;k<linhas;k++) {
					if(k != i) {
						if(matriz[k][j] != 0) {
							aux = matriz[k][j] * -1;
							multiplicar(1,matriz,i,k,colunas,aux);
						}
					}
				}
			}
		}
	}

}

#endif
