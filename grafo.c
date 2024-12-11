#include <stdio.h>
#include <stdlib.h>

typedef struct vertice Vertice;
struct vertice{
    int rotulo;
    Vertice  *proximo;
};

typedef struct Lista lista;
struct Lista{
    Vertice *head;
};  

typedef struct grafo Grafo;
struct grafo{
   lista **lista_adjacencias;
   int n_vertices;
   int n_arestas;
   Vertice v;
   int Aresta;
};

Grafo* cria_grafo(int n){
    Grafo *GRAFO = malloc(sizeof (GRAFO));

    GRAFO->n_vertices = n;
    GRAFO->n_arestas = 0;
    GRAFO->lista_adjacencias = malloc(n * sizeof(lista*));

    for(int i=0; i < n; i++){
        GRAFO->lista_adjacencias[i] = malloc(sizeof (lista));
        GRAFO->lista_adjacencias[i]->head = NULL;
    }    
    return GRAFO;
}
void inicializa_grafo(Grafo *G, int n){
    Grafo *GRAFO = malloc(sizeof (GRAFO));
    G->n_vertices = n;
    
    if(G != NULL){

        for(int i=0; i < G->n_vertices; i++){
            for(int j=i; j <= G->n_vertices; j++){
                GRAFO->lista_adjacencias[i] =  i;
                insere_aresta(GRAFO,i,j);
            }    
        }
    }
}
void imprime_grafo(Grafo *G, FILE * saida){
Vertice *p;

    fprintf(saida, "%d %d\n", G->n_vertices, G->n_arestas);
    for (int i = 0; i < G->n_vertices; i++) {
        for (p = G->lista_adjacencias[i]; p != NULL; p = p->proximo) {
            fprintf(saida, "%2d", p->rotulo);
        }
        fprintf(saida, "-1\n");
    }
}
void insere_vertice(Grafo *G, Vertice *vinse){
    Vertice *ve;
    Vertice *atual;
    Vertice *aux;

    if(G != NULL){
        for(int i=0; i <G->n_vertices; i++){
            atual = G->lista_adjacencias[i]->head;

            if(atual == NULL){
                atual = vinse;
            }
        }
    }
}
void insere_aresta(Grafo *G, int v1, int v2){

    if(v1 > 0 && v2 >0)
        G->lista_adjacencias[v1][v2] = G->Aresta;
}

//void atualiza_adjacencia(Grafo G, Vertice V){

//}

int main(){
    int n;
    Grafo *G;

    printf("informe a quantidade de vertices do grafo: ");
    scanf("%d", &n);

cria_grafo(n);

    FILE *arquivo = fopen("saida.txt", "w");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
    }
imprime_grafo(G, arquivo);
fclose(arquivo);
}
