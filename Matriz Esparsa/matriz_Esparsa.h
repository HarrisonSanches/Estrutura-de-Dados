#ifndef MATRIZ_ESPARSA
#define MATRIZ_ESPARSA

typedef struct celula Celula;
typedef struct matriz Matriz;

Matriz* Matriz_Criar(int tamanho_Matriz);
Matriz* insere_Celula(Matriz* matriz_Criada, int linha_Arquivo, int coluna_Arquivo, float elemento);
Matriz* remove_Celula(Matriz* matriz_Criada, int linha_Arquivo, int coluna_Arquivo, float elemento);
Matriz* soma_Matriz(Matriz* matriz_Criada, Matriz* matriz_Criada2);
void print_Matriz(Matriz *matriz_Criada);
void desaloca_Matriz(Matriz *matriz_Criada);

#endif