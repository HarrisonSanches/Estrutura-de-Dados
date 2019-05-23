#include <stdio.h>
#include <stdlib.h>
#include "matriz_Esparsa.h"

//Struct Celula conforme especificação do trabalho
struct celula {

    int linha, coluna;
    float elemento;
    struct celula* prox_CelLinha;
    struct celula* prox_CelColuna;

};

/*Struct Matriz conforme especificação do trabalho.
A struct contem um vetor de ponteiros para linha e coluna da matriz.*/
struct matriz{

    int tamanho_Matriz;
    struct celula** matriz_Linha;
    struct celula** matriz_Coluna;

};

//Funcao que aloca e cria a matriz.
Matriz* Matriz_Criar(int tamanho_Matriz){

    Matriz* nova_Matriz = (Matriz*)malloc(sizeof(Matriz));
    nova_Matriz->tamanho_Matriz = tamanho_Matriz; 
    nova_Matriz->matriz_Linha = (Celula**)malloc(tamanho_Matriz*sizeof(Celula*));
    nova_Matriz->matriz_Coluna = (Celula**)malloc(tamanho_Matriz*sizeof(Celula*));

    int i = 0;
    while (i < tamanho_Matriz){

        nova_Matriz->matriz_Linha[i] = NULL;
        nova_Matriz->matriz_Coluna[i] = NULL;
        i++;
    }

    return nova_Matriz;
}

//Funcao que cria as celula de acordo com os parâmetros de entrada.
Celula* cria_Celula(int linha_Arquivo, int coluna_Arquivo, float elemento_Arquivo)
{
    Celula* celula_Criada = (Celula*) malloc(sizeof(Celula));
    celula_Criada->linha = linha_Arquivo;
    celula_Criada->coluna = coluna_Arquivo;
    celula_Criada->elemento = elemento_Arquivo;
    celula_Criada->prox_CelLinha = NULL;
    celula_Criada->prox_CelColuna = NULL;

    return celula_Criada;
}


//Funcao que verifica se existe uma celula em determinada posição da matriz!
Celula* verifica_existencia(Matriz* matriz_Criada, int linha_Arquivo, int coluna_Arquivo){
    Celula* celula_Verificadora = matriz_Criada->matriz_Linha[linha_Arquivo];
    int i = 1;
    // Celula auxiliar criada para não forçar um return dentro do while.
    Celula* aux = NULL;
    while(celula_Verificadora != NULL && celula_Verificadora->coluna < matriz_Criada->tamanho_Matriz && i) {
        if (celula_Verificadora ->linha == linha_Arquivo && celula_Verificadora-> coluna == coluna_Arquivo ){
		    aux= celula_Verificadora; 
            i = 0; 
        }
        celula_Verificadora = celula_Verificadora->prox_CelColuna;
    }
    return aux;
 }   

//Funçao que remove uma celula de uma matriz. 
Matriz* remove_Celula(Matriz* matriz_Criada, int linha_Arquivo, int coluna_Arquivo, float elemento){
    
    //verifica se a celula existe naquela posicao.
    Celula* celula_Remover = verifica_existencia(matriz_Criada,linha_Arquivo,coluna_Arquivo);
    //caso exista a célula...
    if (celula_Remover){
        //Celula criada para salvar a celula anterior do elemento.
        Celula* celula_Anterior = NULL;
        Celula* celula_Percorrer = matriz_Criada->matriz_Linha[linha_Arquivo];
        
        //Andando pela coluna...
        while ((celula_Percorrer -> prox_CelColuna != NULL) && (celula_Percorrer -> coluna < coluna_Arquivo)){
        
            celula_Anterior = celula_Percorrer;
            celula_Percorrer = celula_Percorrer->prox_CelColuna;
            
        }
        //Caso onde existe apena um elemento.
        if (celula_Anterior == NULL){
            matriz_Criada->matriz_Linha[linha_Arquivo] = NULL;
        
        }
        //Fazendo o encadeamento.
        else {
            celula_Anterior->prox_CelColuna = celula_Percorrer->prox_CelColuna;
        }

        Celula* celula_Anterior2 = NULL;
        Celula* celula_percorrer2 = matriz_Criada->matriz_Coluna[coluna_Arquivo];
        
        //Andando pela linha...
        while ((celula_percorrer2 -> prox_CelLinha != NULL) && (celula_percorrer2 -> linha < linha_Arquivo)){
        
            celula_Anterior2 = celula_percorrer2;
            celula_percorrer2 = celula_percorrer2->prox_CelLinha;
            
        }
        // caso onde existe apenas um elemento.
        if (celula_Anterior2 == NULL){
            matriz_Criada->matriz_Coluna[coluna_Arquivo] = NULL;
        
        }
        //Fazendo o encadeamento.
        else {
            celula_Anterior2->prox_CelLinha = celula_percorrer2->prox_CelLinha;
        }
    
    
    //free a celula que foi removida.
    free(celula_Remover);
    return matriz_Criada;
    }
    //caso nao exista celula naquela posicao...
    else {
        return matriz_Criada;
    }

}


/*Funcao que insera uma celula na matriz.
A funcao considera que os arquivos de entrada estarão ordenados por linha e coluna
conforme especificação.*/

Matriz* insere_Celula(Matriz* matriz_Criada, int linha_Arquivo, int coluna_Arquivo, float elemento){

    //Verificando se ja existe uma celula naquela posicao.
    Celula* celula_Teste = verifica_existencia(matriz_Criada,linha_Arquivo,coluna_Arquivo);

    // if elemento for 0 e exista a celula, remove.
    if (elemento == 0.0){
        
        if (celula_Teste){
            remove_Celula(matriz_Criada, linha_Arquivo, coluna_Arquivo, elemento);
            return matriz_Criada;
        }
        else{
            return matriz_Criada;
        }
    }   
    
    //If existe e é diferente de zero, substitui o elemento.
    if (celula_Teste){
        celula_Teste -> elemento = elemento;
        return matriz_Criada;
    }

    //cria nova celula.
    Celula* nova_Celula = cria_Celula(linha_Arquivo, coluna_Arquivo, elemento);

    //Verificando condicoes de borda    
    if (linha_Arquivo > matriz_Criada->tamanho_Matriz || linha_Arquivo < 0 || coluna_Arquivo > matriz_Criada->tamanho_Matriz || coluna_Arquivo < 0) {
        free(nova_Celula);
        return matriz_Criada;
    } 
    
    //Caso a linha esteja vazia...    
    if (matriz_Criada->matriz_Linha[linha_Arquivo] == NULL) {
        matriz_Criada->matriz_Linha[linha_Arquivo] = nova_Celula;
    }
    else {
        //insere
        Celula* celula_percorrer = matriz_Criada -> matriz_Linha[linha_Arquivo];   
        while (celula_percorrer -> prox_CelColuna != NULL){
            celula_percorrer = celula_percorrer->prox_CelColuna;
        }
        celula_percorrer -> prox_CelColuna= nova_Celula;
    }

    //Caso a coluna esteja vazia..
    if (matriz_Criada->matriz_Coluna[coluna_Arquivo] == NULL) {
        matriz_Criada->matriz_Coluna[coluna_Arquivo] = nova_Celula;
        }
    else {
        //insere
        Celula* celula_percorrer = matriz_Criada -> matriz_Coluna[coluna_Arquivo];   
        while (celula_percorrer -> prox_CelLinha != NULL) {
            celula_percorrer = celula_percorrer->prox_CelLinha;
        }
        celula_percorrer -> prox_CelLinha = nova_Celula;
    }

    return matriz_Criada;
}


//Funcao que soma duas matrizes.
Matriz* soma_Matriz(Matriz* matriz_Criada, Matriz* matriz_Criada2){

    Matriz* matriz_Soma = Matriz_Criar(matriz_Criada -> tamanho_Matriz);
    float resultado_Soma;
    
    //Veriricação de possibilidade de soma
    if (matriz_Criada-> tamanho_Matriz != matriz_Criada2 -> tamanho_Matriz){
     
        return NULL;
    }
    else{
        /*Caso de pra somar, a função percorre as duas matrizes ao mesmo tempo.*/
        
        for (int i = 0; i < matriz_Criada -> tamanho_Matriz; i++){
            //Celulas para percorrer as matrizes
            Celula* celula_Matriz1 = matriz_Criada -> matriz_Linha[i];
            Celula* celula_Matriz2 = matriz_Criada2 -> matriz_Linha[i];  
            
            while (celula_Matriz1 != NULL || celula_Matriz2 != NULL)  {
                //Significa que tem celula nas duas linhas da matrizes
                if ( (celula_Matriz1 != NULL) && (celula_Matriz2 != NULL) ) {
                    //se elas tiverem as mesmas colunas, entao eu somo os elementos, pois estao nas mesmas posicoes.
                    if (celula_Matriz1 -> coluna == celula_Matriz2 -> coluna){
                        resultado_Soma =  celula_Matriz1 -> elemento + celula_Matriz2 -> elemento;
                        if (resultado_Soma != 0) {
                            matriz_Soma = insere_Celula(matriz_Soma,celula_Matriz1 -> linha, celula_Matriz1 -> coluna, resultado_Soma);
                            celula_Matriz1 = celula_Matriz1->prox_CelColuna;
                            celula_Matriz2 = celula_Matriz2->prox_CelColuna;
                        }
                    }
                    // senao, verifico qual tem a coluna menor.
                    else {
                        // caso a celula2 tenha coluna menor, insiro a mesma e faco apenas a celula 2 receber a celula da proxima coluna.
                        if (celula_Matriz1 -> coluna > celula_Matriz2 -> coluna){
                            matriz_Soma = insere_Celula(matriz_Soma,celula_Matriz2 -> linha, celula_Matriz2 -> coluna,celula_Matriz2 -> elemento);
                            celula_Matriz2 = celula_Matriz2 -> prox_CelColuna;
                        }
                        else {
                            //a celula 1 tem a menor coluna e faco apenas a celula 1 receber a proxima coluna, deixando a celula 2 parada.
                            matriz_Soma = insere_Celula(matriz_Soma,celula_Matriz1 -> linha, celula_Matriz1 -> coluna,celula_Matriz1 -> elemento);
                            celula_Matriz1 = celula_Matriz1 -> prox_CelColuna;
                        }
                    }
                }    
                //Caso entre aqui, uma das linhas nao tem mais celulas ou uma linha nao tem celula, logo...
                else{
                    if (celula_Matriz1 == NULL){
                        matriz_Soma = insere_Celula(matriz_Soma,celula_Matriz2 -> linha, celula_Matriz2-> coluna,celula_Matriz2 -> elemento);
                        celula_Matriz2 = celula_Matriz2 -> prox_CelColuna;
                    }
                    else {
                        matriz_Soma = insere_Celula(matriz_Soma,celula_Matriz1 -> linha, celula_Matriz1-> coluna,celula_Matriz1 -> elemento);
                        celula_Matriz1 = celula_Matriz1 -> prox_CelColuna;
                    }
                }
            
            }    
        }
    }
    return matriz_Soma;   
}  

//funcao que desaloca uma matriz.
void desaloca_Matriz(Matriz *matriz_Criada)
{
	//percorro as linhas da matriz e vou eliminando as celulas seguintes...
    for(int i = 0; i < matriz_Criada->tamanho_Matriz; i++)
	{
		Celula* celula_Percorrer = matriz_Criada->matriz_Linha[i];
		Celula* celula_Anterior = NULL;
		while(celula_Percorrer != NULL)
		{
			celula_Anterior = celula_Percorrer;
			celula_Percorrer = celula_Percorrer ->  prox_CelColuna;
            free(celula_Anterior);
        }
    //caso ainda tenha algo na celula pra percorrer...
    free(celula_Percorrer);
    }
	//desaloco as linhas e colunas da matriz
    free(matriz_Criada -> matriz_Linha);
	free(matriz_Criada -> matriz_Coluna);
    // por fim, desaloco a matriz.
    free(matriz_Criada);
}

//funcao que printa a matriz na tela
void print_Matriz(Matriz* matriz_Criada) {
	//Percorro por linhas e vou andando pelas colunas da matriz.
    for(int i = 0; i < matriz_Criada->tamanho_Matriz; i++){
		//celula pra percorrer a matriz. Ela recebe sempre a cabeca da linha.
        Celula* celula_Percorre = matriz_Criada->matriz_Linha[i];
        while (celula_Percorre != NULL){
			printf("%d; %d; %.2f\n", celula_Percorre->linha+1, celula_Percorre->coluna+1, celula_Percorre->elemento);
            celula_Percorre = celula_Percorre->prox_CelColuna;
        }
    }
}


	