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

Grafo* cria_grafo(){
    int n = 5;
    Grafo *GRAFO = malloc(sizeof (GRAFO));

    GRAFO->n_vertices = n;
    GRAFO->n_arestas = 4;
    GRAFO->lista_adjacencias = malloc(n * sizeof(lista*));

    for(int i=0; i < n; i++){
        GRAFO->lista_adjacencias[i] = malloc(sizeof (lista));
        GRAFO->lista_adjacencias[i]->head = NULL;
    }
    return GRAFO;
}
void inicializa_grafo(Grafo *G){
    Grafo *GRAFO = malloc(sizeof (GRAFO));

    if(G != NULL){

        for(int i=0; i < G->n_vertices; i++){
            for(int j=0; j <= G->n_arestas; j++){
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
void imprime_matriz(Grafo *G){

    for(int i=0; i < G->n_vertices; i++){
        for(int j=0; j< G->n_arestas; j++){
            printf("%d -> %d", G->lista_adjacencias[i][j]);
        }
    }
}
void insere_vertice(Grafo *G, Vertice *vinse){

    Vertice *atual = malloc(sizeof (Vertice));

    if(G != NULL){
        for(int i=0; i < G->n_vertices; i++)
            atual = G->lista_adjacencias[i]->head;
             if(atual == NULL){
                atual = vinse;

            G->n_vertices++;
        }
    }
}
int buscar(Grafo * G, Vertice *v){
 
    for(int i=0; i < G->n_vertices; i++){
        for(int j=0; j < G->n_vertices; j++){
            
            if(G->lista_adjacencias[i] == v)
                return v;
        }
    }
}
void insere_aresta(Grafo *G, int v1, int v2){

    for(int i=0; i < G->n_vertices; i++)
        if(v1 > 0 && v2 >0)
            G->lista_adjacencias = G->lista_adjacencias[v1][v2] = 1;

    G->n_arestas++;
}

voi remove_vertice(Vertice *v, Grafo *G){

}
void remove_aresta()

//void atualiza_adjacencia(Grafo G, Vertice V){

//}

int main(){
    Grafo *G;

cria_grafo();

    FILE *arquivo = fopen("saida.txt", "w");

    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
    }
imprime_grafo(G, arquivo);
fclose(arquivo);
}
