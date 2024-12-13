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
   Vertice *v;
   Vertice *Aresta;
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

    if(G != NULL){

        for(int i=0; i < G->n_vertices; i++){
                G->lista_adjacencias[i]->head = i+1;
        }
          insere_aresta(G,1,2);
          insere_aresta(G,2,3);
          insere_aresta(G,3,4);
          insere_aresta(G,4,5);
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
        for(int i=0; i < G->n_vertices; i++){
            atual = G->lista_adjacencias[i]->head;
                 if(atual == NULL){
                    atual = vinse;

                G->n_vertices++;
            }
        }
    }
}
int buscar(Grafo * G, Vertice *V){

        while(V < G->v && V->proximo != NULL){
            if(G->lista_adjacencias == V)
            return V;
        }
}
void insere_aresta(Grafo *G, Vertice *v1, Vertice *v2){

    Vertice *aux2 = malloc(sizeof (Vertice));
    Vertice *aux = G->lista_adjacencias[v1]->head;

    while(v1 < G->v && v1->proximo != NULL){
        if(v1 > 0 && v2 >0){
            G->Aresta[v1]->proximo = G->lista_adjacencias[v2]->head;
            aux = v1->proximo;
            aux2 = aux->proximo;
        }
    }
    G->n_arestas++;
}

void remove_vertice(Vertice *v, Grafo *G){
    int adj[10];
    Vertice *aux = G->lista_adjacencias[v]->head;
    int soma=0;
    Vertice *atual = malloc(sizeof (Vertice));

    if(v != NULL){
        for(int i=0; i < G->n_vertices; i++){
            if( i == v ){

                for(int j=0; j< G->n_vertices; j++){
                    adj[j] = aux;
                    aux = aux->proximo;
                }
            }
        }
        aux = G->lista_adjacencias[v]->head;
        atual = aux;
        while(aux != NULL && adj[soma] == v){
            aux = atual;
            atual = atual->proximo;
            soma++;
        }
        free(aux);
    }
}

void remove_aresta(){

}

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
