#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matriz_Esparsa.h"

int main(int argc, char *argv[])
{
    //Definindo as matrizes
	Matriz* matriz1;
    Matriz* matriz2;
    Matriz* matriz_Soma;
	
	// Definindo os paramentros de entrada dos arquivos
	char *nome_Arquivo1 = argv[1];
	char *nome_Arquivo2 = argv[2];
	FILE *pointer_File1 = fopen(nome_Arquivo1, "rt");
	FILE *pointer_File2 = fopen(nome_Arquivo2, "rt");

	int linha, coluna, tamanho;
	float elemento;
	
	// Lendo a primeira linha do arquivo pra definir o tamanho da matriz 1
    fscanf(pointer_File1 , "%d", &tamanho);
	matriz1 = Matriz_Criar(tamanho);

    //Lendo a primeira linha do arquivo pra definir o tamanho da matriz 2
    fscanf(pointer_File2, "%d", &tamanho);
	matriz2 = Matriz_Criar(tamanho);

	//lendo os elementos do arquivo até acabar as linhas
	while(fscanf(pointer_File1, "%d;%d;%f ", &linha, &coluna, &elemento) != EOF) {
		matriz1 = insere_Celula(matriz1, linha-1, coluna-1, elemento);
	}

	while(fscanf(pointer_File2, "%d;%d;%f", &linha, &coluna, &elemento) != EOF) {
		matriz2 = insere_Celula(matriz2, linha-1, coluna-1, elemento);
	}
	
    matriz_Soma = soma_Matriz(matriz1, matriz2);
	
	//print matriz soma, fechando arquivos e desalocando a matriz.
	print_Matriz(matriz_Soma);
	fclose(pointer_File1);
	fclose(pointer_File2);

    desaloca_Matriz(matriz_Soma);
    
    return 0;
}
    
    