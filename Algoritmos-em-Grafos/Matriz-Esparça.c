#include <stdio.h> 
#include <string.h>
#include <math.h>
#include <stdlib.h>

typedef struct Cell Cell;
typedef struct ListaE ListaE;
typedef struct Spa_Mat Spa_Mat;

struct Cell{
        int item;
        int col;
        Cell *next;
};


struct ListaE{
        Cell *head;
};


struct Spa_Mat{
    int n_lin;
    int n_col;
       ListaE **lin;
};


Spa_Mat* criar(int l, int c){
        Spa_Mat* mat = (Spa_Mat*) malloc(sizeof(Spa_Mat));
        int i;

        mat->n_col = c;
        mat->n_lin = l;
        mat->lin = (ListaE*) malloc(sizeof(ListaE) * l);

        for (i = 0; i < l; i++){
            mat->lin[i] = (ListaE*) malloc(sizeof(ListaE));
            mat->lin[i]->head = NULL;
        }

        return mat;
}


Cell* criar_celula(int item, int col){
    Cell * nova = (Cell*) malloc(sizeof(Cell));
    nova->item = item;
    nova->col = col;
    nova->next = NULL;

    return nova;
}


static int procurar_lista(int item, ListaE *l){
        Cell *aux = NULL;

        if (l != NULL){
                aux = l->head;

                while ((aux != NULL) && (aux->item != item))
                    aux = aux->next;
        }

        if((aux != NULL) && (aux->item == item))
        {
            return 1;
        }
        else
                return 0;
}


int buscar(int item, Spa_Mat* mat){
        int i;
        int aux = 0;

        for (i = 0; ((i < mat->n_lin) && (aux == 0)); i++)
                aux = procurar_lista(item, mat->lin[i]);

        return aux;
}


static int validar_pos_matriz(int lin, int col, Spa_Mat* mat){
    return (mat != NULL) && (lin >= 0) && (lin < mat->n_lin) && (col >= 0) && (col < mat->n_col);
}


int buscar_posicao(int l, int c, Spa_Mat* mat){
    Cell *aux;
    int valor = 0;

    if ((mat != NULL) && validar_pos_matriz(l, c, mat)){
        aux = mat->lin[l]->head;

        while ((aux != NULL) && (c > aux->col))
            aux = aux->next;

        if ((aux != NULL) && (c == aux->col))
            valor = aux->item;
    }

    return valor;
}


static void trocar_inserir_na_lista(int item, int col, ListaE *l){
    Cell *auxA, *auxP, *novo;

    if ((l->head == NULL) || (col < l->head->col)){
        novo = criar_celula(item, col);
        novo->next = l->head;
        l->head = novo;
    }else if (col == l->head->col){
        l->head->item = item;
    }else{
        auxA = l->head;
        auxP = auxA;

        while ((auxP != NULL) && (auxP->col < col)){
            auxA = auxP;
            auxP = auxP->next;
        }

        if ((auxP != NULL) && (col == auxP->col))
            auxP->item = item;
        else{
            novo = criar_celula(item, col);
            novo->next = auxA->next;
            auxA->next = novo;
        }
    }
}


static void remover_na_lista(int col, ListaE *l){
    Cell *auxA, *auxP = NULL;

    if (l->head != NULL){
        if (col == l->head->col){
            auxP = l->head;
            l->head = l->head->next;
            free(auxP);
        }else{
            auxA = l->head;
            auxP = auxA;

            while ((auxP != NULL) && (auxP->col < col)){
                auxA = auxP;
                auxP = auxP->next;
            }

            if ((auxP != NULL) && (col == auxP->col)){
                auxA->next = auxP->next;

                free(auxP);
            }
        }
    }
}

void trocar(int item, int l, int c, Spa_Mat* mat){
    if (validar_pos_matriz(l, c, mat)){
        if (item > 0)
            trocar_inserir_na_lista(item, c, mat->lin[l]);
        else
            remover_na_lista(c, mat->lin[l]);
    }
}

void imprimir(Spa_Mat* mat)
{
    Cell *aux;

    for(int i = 0; i < mat->n_lin; i++)
    {
        aux = mat->lin[i]->head;
        int j = 0;

        while(aux != NULL)
        {
            while(j < aux->col)
            {
                printf("0 ");
                j++;
            }

            printf("%d ", aux->item);
            j++;
            aux = aux->next;
        }

        while(j < mat->n_col)
        {
            printf("0 ");
            j++;
        }

        printf("\n");
    }
}
Spa_Mat * multiplica_matriz(Spa_Mat * m1, Spa_Mat * m2){
    int lin1 = m1->n_lin;
    int col1 = m1->n_col;
    int lin2 = m2->n_lin;
    int col2 = m2->n_col;
    int maior = 0;
    int l, c;

    if(lin1 > lin2)
        l = lin1;
    else
        l = lin2;

    if(col1 > col2)
        c = col1;
    else
        c = col2;

    Spa_Mat *m3 = criar(l, c);

        if(l > c)
            maior = l;
        else
            maior = c;

    for(int k=0; k <= maior; k++){
        for(int i = 0; i <= l; i++ ){
            int soma=0;
            for(int j=0; j <= c; j ++)
                  soma += buscar_posicao(k,i,m1) * buscar_posicao(j,i,m2);
            
            trocar(soma, k-1, i-1, m3);
        }
    }
    
    return m3;
}

Spa_Mat *somar_matrizes(Spa_Mat *m1, Spa_Mat *m2){
    int lin1 = m1->n_lin;
    int col1 = m1->n_col;
    int lin2 = m2->n_lin;
    int col2 = m2->n_col;
    int l, c;

    if(lin1 > lin2)
        l = lin1;
    else
        l = lin2;

    if(col1 > col2)
        c = col1;
    else
        c = col2;

    Spa_Mat *m3 = criar(l, c);

    for(int i = 0; i < l; i++)
    {
        for(int j = 0; j < c; j++)
        {
            int item1 = buscar_posicao(i, j, m1);
            int item2 = buscar_posicao(i, j, m2);
            int soma = item1 + item2;

            if (soma != 0)
            {
                trocar(soma, i, j, m3);
            }
        }
    }
    return m3;
}
void apaga_matriz( Spa_Mat * mat){                      

    Cell * celula_atual;
    Cell * next_celula;
    ListaE * lista;

    if( mat != NULL){ 
        for(int i=0; i < mat->n_lin; i++){

            lista = mat->n_lin[i];
            celula_atual = lista->head;

            while(celula_atual != NULL){
                next_celula = celula_atual->next;

                free(celula_atual);

                celula_atual = next_celula;
            } 
            free(lista);
        }  
        free(mat->n_lin);
    
    free(mat);
}
Spa_Mat * cria_transposta(Spa_Mat * mat, int l, int c){
     
     Cell * aux = criar_celula(mat->lin->head,c);
     Cell * aux2 = criar_celula(mat->lin->head,c);
     Spa_Mat * transposta = criar(l,c);

        if(mat != NULL){ 
            for(int i=0; i < mat->n_lin; i++){
                for(int j=0; j < = i; j++){   // quando j = i ele não executara a parte de cima
                    if(mat->n_lin[i] != mat->n_col[j]){              //pq se os indices forem iguais irá manter o item da quela posição 
                        aux-> item = buscar_posicao(i,j,mat);
                        aux2-> item = buscar_posicao(j,i,mat);
                        trocar(aux->item,j,i,transposta);
                        trocar(aux2->item,i,j,transposta);
                    }else{
                        aux-> item = buscar_posicao(j,i,mat);
                        trocar(aux->item,j,i,transposta);   
                    }          
                }
            }
        }
    free(aux);
    free(aux2);

    return transposta;
}

int main(void){

    int l1, c1, l2, c2, item, opcao;
    Spa_Mat *m3 = multiplica_matriz(m1, m2);

     printf("\n insira a matriz: \n");
    scanf("%d %d", &l1, &c1);

    Spa_Mat *m1 = criar(l1, c1);

    for(int i = 0; i < l1; i++)
    {
        for(int j = 0; j < c1; j++)
        {
            scanf("%d", &item);
            if(item != 0)
            {
                trocar(item, i, j, m1);
            }
        }
    }
    printf("\n insira a segunda matriz: \n");
    scanf("%d %d", &l2, &c2);

    Spa_Mat *m2 = criar(l2, c2);

    for(int i = 0; i < l2; i++)
    {
        for(int j = 0; j < c2; j++)
        {
            scanf("%d", &item);
            if(item != 0)
            {
                trocar(item, i, j, m2);
            }
        }
    }
    printf("\n 1- multiplica matriz \n 2- soma matriz \n 3- apaga matriz_m1\n 4-apaga matriz_m2\n 5- cria trasposta_m1\n 6- cria trasposta_m2");
    scanf("%d", &opcao);
     
     switch (opcao)
     {
     case '5':
        imprimir(m1);
        printf("\n transposta da matriz \n");
        m3 = cria_transposta(m1,l1,c1);
        imprimir(m3);
        break;
     case '1':
        m3 = multiplica_matriz(m1,m2);
        imprimir(m1);
        printf("\n * \n");
        imprimir(m2);
        printf("\n == \n");
        imprimir(m3);
        break;
     case '2':
        m3 = somar_matrizes(m1,m2);
        imprimir(m1);
        printf("\n * \n");
        imprimir(m2);
        printf("\n == \n");
        imprimir(m3);
        break;
     case '3':
        apaga_matriz(m1);
        system("clear");
        break;
     case '4':
        apaga_matriz(m2);
        system("clear");
        break;
     case '6':
        imprimir(m2);
        printf("\n transposta da matriz \n");
        m3= cria_transposta(m2,l2,c2);
        imprimir(m3);
        break;
     }

    return 0;
}
