#include <stdio.h>
#include <stdlib.h>

typedef struct Vertice Vertice;
typedef struct lista lista;
typedef struct Grafo Grafo;

struct Vertice{
    int rotulo;
    Vertice *proximo;
};

struct lista{
    Vertice *head;
};

struct Grafo{
    int n_vertices;
    int n_arestas;
    lista **lista_adjacencias;
};

Grafo *cria_grafo(int v){
    Grafo *G = (Grafo*)malloc(sizeof(Grafo));

    G->n_vertices = 0;
    G->n_arestas = 0;
    G->lista_adjacencias = (lista**)malloc(sizeof(lista*) * v);

    for(int i = 0; i < G->n_vertices; i ++){
        G->lista_adjacencias[i] = (lista*)malloc(sizeof(lista));
        G->lista_adjacencias[i]->head = NULL;
    }
    return G;
}

void insere_vertice(Grafo *G, int rotulo){
    if(G != NULL && rotulo >= 0){
        Vertice *novo_vertice = (Vertice*)malloc(sizeof(Vertice));
        novo_vertice->rotulo = rotulo;
        novo_vertice->proximo = NULL;

        G->lista_adjacencias[G->n_vertices] = (lista*)malloc(sizeof(lista));
        G->lista_adjacencias[G->n_vertices]->head = novo_vertice;

        G->n_vertices++;
    }
}

int buscar_indice_Rotulo(Grafo *G, int v){
    for(int i = 0; i < G->n_vertices; i++){
        Vertice *aux = G->lista_adjacencias[i]->head;

        if(aux->rotulo == v)
            return i;
    }

    return -1;
}

void insere_aresta(Grafo *G, int v1, int v2){
    if(G != NULL){
        int id_v1 = buscar_indice_Rotulo(G, v1);
        int id_v2 = buscar_indice_Rotulo(G, v2);

        if((id_v1 != -1) && (id_v2 != -1)){
            Vertice *aux_v2 = malloc(sizeof(Vertice));
            aux_v2->rotulo = v2;
            aux_v2->proximo = NULL;

            if(G->lista_adjacencias[id_v1]->head == NULL)
                G->lista_adjacencias[id_v1]->head = aux_v2;
            else{
                Vertice *aux = G->lista_adjacencias[id_v1]->head;
                while(aux->proximo != NULL)
                    aux = aux->proximo;

                aux->proximo = aux_v2;
            }

            Vertice *aux_v1 = malloc(sizeof(Vertice));
            aux_v1->rotulo = v1;
            aux_v1->proximo = NULL;

            if(G->lista_adjacencias[id_v2]->head == NULL)
                G->lista_adjacencias[id_v2]->head = aux_v1;
            else{
                Vertice *aux = G->lista_adjacencias[id_v2]->head;
                while(aux->proximo != NULL)
                    aux = aux->proximo;

                aux->proximo = aux_v1;
            }

            G->n_arestas++;
        }
    }
}
void remove_vertice(Grafo *G, int v){
    if(G != NULL){
        int id_v = buscar_indice_Rotulo(G, v);

        if(id_v != -1){
            for(int i = 0; i < G->n_vertices; i++){ //remover as arestas dos outros vertices que apontam para o v
                if(i != id_v){
                    Vertice *aux = G->lista_adjacencias[i]->head;
                    Vertice *anterior = NULL;
                    while(aux != NULL){
                        if(aux->rotulo == v){
                            if(anterior == NULL)
                                G->lista_adjacencias[i]->head = aux->proximo; //remover o primeiro ponto
                            else
                                anterior->proximo = aux->proximo;  //remover algum do meio ou do fim

                            free(aux);
                            break;
                        }
                        anterior = aux;
                        aux = aux->proximo;
                    }
                }
            }

            Vertice *aux = G->lista_adjacencias[id_v]->head; 
            while(aux != NULL){
                Vertice *temp = aux;
                aux = aux->proximo;
                free(temp);  
            }

            free(G->lista_adjacencias[id_v]); 

            for(int i = id_v; i < G->n_vertices - 1; i++) 
                G->lista_adjacencias[i] = G->lista_adjacencias[i + 1];

            G->n_vertices--;
        }
    }
}

void remove_aresta(Grafo *G, int v1, int v2){
    if(G != NULL){
        int id_v1 = buscar_indice_Rotulo(G, v1);
        int id_v2 = buscar_indice_Rotulo(G, v2);

        if(id_v1 != -1 && id_v2 != -1){
            Vertice *aux = G->lista_adjacencias[id_v1]->head;
            Vertice *anterior = NULL;

            while(aux != NULL){
                if(aux->rotulo == v2){
                    if(anterior == NULL)
                        G->lista_adjacencias[id_v1]->head = aux->proximo;
                    else
                        anterior->proximo = aux->proximo;

                    free(aux);
                    break;
                }
                anterior = aux;
                aux = aux->proximo;
            }

            aux = G->lista_adjacencias[id_v2]->head;
            anterior = NULL;

            while(aux != NULL){
                if (aux->rotulo == v1) {
                    if (anterior == NULL)
                        G->lista_adjacencias[id_v2]->head = aux->proximo;
                    else
                        anterior->proximo = aux->proximo;

                    free(aux);
                    break;
                }
                anterior = aux;
                aux = aux->proximo;
            }

            G->n_arestas--;
        }
    }
}

void imprime_grafo(Grafo *G){
    if(G != NULL){
        for(int i = 0; i < G->n_vertices; i++){
            printf("Vertice %d: ", i + 1);

            Vertice *aux = G->lista_adjacencias[i]->head;

            if(aux != NULL){
                while(aux != NULL){
                    printf("%d -> ", aux->rotulo);
                    aux = aux->proximo;
                }
            }
            printf("\n");
        }
    }
}

void liberar_grafo(Grafo *G){
    if(G != NULL){
        for(int i = 0; i < G->n_vertices; i++){
            Vertice *aux = G->lista_adjacencias[i]->head;
            Vertice *temp;

            while(aux != NULL){
                temp = aux;
                aux = aux->proximo;
                free(temp);
            }

            free(G->lista_adjacencias[i]);
        }

        free(G->lista_adjacencias);

        free(G);
    }
}

void menu() {
    printf("\n--- Menu ---\n");
    printf("1: Inicializar Vertices.\n");
    printf("2: Inserir Arestas.\n");
    printf("3: Visualizar Grafo.\n");
    printf("4: Remover Vertices.\n");
    printf("5: Remover Arestas.\n");
    printf("6: Salvar em Arquivo.\n");
    printf("7: Sair.\n");
    printf("Escolha uma opcao: ");
}

void iniciar_trabalho(Grafo *G){
    insere_vertice(G, 1);
    insere_vertice(G, 2);
    insere_vertice(G, 3);
    insere_vertice(G, 4);
    insere_vertice(G, 5);
    insere_vertice(G, 6);
    insere_vertice(G, 7);
    insere_vertice(G, 8);
    insere_vertice(G, 9);

    insere_aresta(G, 1, 2);
    insere_aresta(G, 1, 6);
    insere_aresta(G, 4, 2);
    insere_aresta(G, 3, 2);
    insere_aresta(G, 3, 5);
    insere_aresta(G, 4, 6);
    insere_aresta(G, 4, 5);
    insere_aresta(G, 4, 7);
    insere_aresta(G, 7, 8);
    insere_aresta(G, 7, 9);
}

void ler_arquivo(Grafo *G, const char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "r");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    int num_vertices;
    fscanf(arquivo, "%d", &num_vertices);
    for(int i = 1; i <= num_vertices; i++)
        insere_vertice(G, i);

    int v1, v2;
    while(fscanf(arquivo, "%d %d", &v1, &v2) != EOF)
        insere_aresta(G, v1, v2);

    fclose(arquivo);
}

void salvar_arquivo(Grafo *G, const char *nome_arquivo){
    FILE *arquivo = fopen(nome_arquivo, "w");
    if(arquivo == NULL){
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    fprintf(arquivo, "%d\n", G->n_vertices);

    for(int i = 0; i < G->n_vertices; i++){
        Vertice *aux = G->lista_adjacencias[i]->head;

        while(aux != NULL){
            if(i + 1 < aux->rotulo)
                fprintf(arquivo, "%d %d\n", i + 1, aux->rotulo);

            aux = aux->proximo;
        }
    }

    fclose(arquivo);
}

int main(void){
    int opcao, V, v1, v2, aresta;
    int verificador = 0;

    printf("O Grafo foi inicializado com 9 vertices.");
    V = 9;

    Grafo *G = cria_grafo(V);
    iniciar_trabalho(G);
    //ler_arquivo(G, "C:/Users/User/Desktop/arquivoGrafo.txt");

    do{
        menu();
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                if(verificador == 0){ 
                    for(int i = 0; i < V; i++){
                        printf("Informe o vertice a ser inicializado (1 a %d): ", V);
                        scanf("%d", &v1);
                        insere_vertice(G, v1);
                        verificador = 1;
                    }
                }else
                    printf("Ja foram inicializados os vertices.");
                break;
            case 2:
                printf("Informe a quantidade de arestas a serem inseridas: ");
                scanf("%d", &aresta);

                for(int i = 0; i < aresta; i++){
                        printf("Informe os vertices v1 e v2 para criar uma aresta: ");
                        scanf("%d %d", &v1, &v2);
                        insere_aresta(G, v1, v2);
                }
                break;
            case 3:
                imprime_grafo(G);
                break;
            case 4:
                printf("Informe o vertice a ser removido: ");
                scanf("%d", &v1);
                remove_vertice(G, v1);
                break;
            case 5:
                printf("Informe os vertices v1 e v2 para remover a aresta: ");
                scanf("%d %d", &v1, &v2);
                remove_aresta(G, v1, v2);
                break;
            case 6:
                salvar_arquivo(G, "salvarGrafo.txt");
                printf("Grafo salvo com sucesso no arquivo 'salvarGrafo.txt'.\n");
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }while(opcao != 7);

    liberar_grafo(G);
    return 0;
}
