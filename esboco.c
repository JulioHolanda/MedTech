
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//aqui vai o remédio
struct node{
    char nome[100];
    char princ_ativo[100];
    char tipo[100];
    char ref[100];
    char lab[50];
    char codigo[10];
    struct node *next;
};

void insertNode(struct node **head);
void insertFromText(struct node **head, char nome[], char princ[], char tipo[], char ref[], char lab[], char cod[]);
void printando(struct node *head);
void removeNode(struct node **head, char nome[], char lab[]);
void buscaElemento(struct node **head, char nome[]);
void printSemelhantes(struct node *head, char nome[]);

int main(){
    FILE *bdd;
    int opt;
    char remedio[100];
    char nome[100];
    char princ_ativo[100];
    char tipo[100];
    char ref[100];
    char lab[50];
    char codigo[10];

    struct node *head = NULL;

    bdd = fopen("bdd.txt", "r");

    for(int i=0; i<9; i++){

        fscanf(bdd, " %s %s %s %s %s %s", nome, princ_ativo, tipo, ref, lab, codigo);
        insertFromText(&head, nome, princ_ativo, tipo,ref, lab, codigo);
    }

    fclose(bdd);

    while(1){ //menu interativo
        printf("\nQue acao voce deseja fazer:\n"
        "1: adicionar remedio\n"
        "2: consultar por genpericos e similares\n"
        "0: sair:\n");

        scanf(" %d",  &opt);

        if ( opt == 1){ //adicionar remédio

            insertNode(&head);

        }else if (opt == 2){  //consulta de remédios

            printf("Por qual medicamento deseja porcurar?\n");
            scanf(" %[^\n]", &remedio);
            buscaElemento(&head, remedio);

        }else if (opt ==0){   // sair do rograma

            break;

        }else { // qualquer outra entrada

            printf(" \n --INSIRA UMA OPÇÃO VÁLIDA -- \n");
        }
    }

    return 0;
}

void insertFromText(struct node **head, char nome[], char princ[], char tipo[], char ref[], char lab[], char cod[]){

    struct node *novo = (struct node*)malloc(sizeof(struct node));
    struct node *aux;

    //caso espaço criado, preenche dados do node
    if (novo!= NULL){
        strcpy(novo->nome, nome);
        strcpy(novo->princ_ativo, princ);
        strcpy(novo->tipo, tipo);
        strcpy(novo->ref, ref);
        strcpy(novo->lab, lab);
        strcpy(novo->codigo, cod);

    }
    if((*head)==NULL){  //ta vazia
        (*head)=novo;
        (*head)->next = NULL;

    }else if(strcmp(novo->nome,(*head)->nome)<0){ //antes do head
        novo->next = *head;
        *head= novo;
    }else if(strcmp(novo->nome,(*head)->nome)==0){ //semelhante ao head
        novo->next = (*head)->next;
        (*head)->next = novo;

    }else{
        aux = *head;

        while(1){ //navegando enquanto lista nao acaba ou fora de posiçao (alfabética)
            if(aux->next == NULL ||strcmp(novo->nome,aux->next->nome)<=0){
                novo->next = aux->next;
                aux->next = novo;
                break;
            }
            aux=aux->next;
        }
    }
}

void insertNode(struct node **head){
    struct node *novo = (struct node*)malloc(sizeof(struct node));
    struct node *aux;

    //caso espaço criado, preenche dados do node
    if (novo!= NULL){
        printf("Nome: ");
        scanf(" %[^\n]", &novo->nome);
        printf("Principio ativo: ");
        scanf(" %[^\n]", &novo->princ_ativo);
        printf("Tipo: ");
        scanf(" %[^\n]", &novo->tipo);
        printf("Referencia: ");
        scanf(" %[^\n]", &novo->ref);
        printf("Laboratorio: ");
        scanf(" %[^\n]", &novo->lab);
        printf("Codigo de barras: ");
        scanf(" %[^\n]", &novo->codigo);

    }
    if((*head)==NULL){  //ta vazia
        (*head)=novo;
        (*head)->next = NULL;

    }else if(strcmp(novo->nome,(*head)->nome)<0){ //antes do head
        novo->next = *head;
        *head= novo;
    }else if(strcmp(novo->nome,(*head)->nome)==0){ //semelhante ao head
        novo->next = (*head)->next;
        (*head)->next = novo;

    }else{
        aux = *head;

        while(1){ //navegando enquanto lista nao acaba ou fora de posiçao (alfabética)
            if(aux->next == NULL ||strcmp(novo->nome,aux->next->nome)<=0){
                novo->next = aux->next;
                aux->next = novo;
                break;
            }
            aux=aux->next;
        }
    }
}

void buscaElemento(struct node **head, char nome[]){
    struct node *aux = *head;
    char igual[100];

    if (*head != NULL) {
        while (aux != NULL) {
            if (strcmp(aux->nome, nome) == 0){  //se remedio encontrado na lista
                strcpy(igual, aux->princ_ativo);
                printSemelhantes(*head, igual);  //imprime remedios de mesmo princp ativo
                break;
            }
        aux = aux->next;
        }
    }
  return NULL;
}

void printSemelhantes(struct node *head, char nome[]){ //print de remedios semelhantes

    while (head != NULL){
        if (strcmp(head->princ_ativo, nome) == 0){ //se de mesmo principio ativo, é printado

            printf("Nome: %s\n"
            "Tipo: %s\n"
            "Laboratorio: %s\n"
            "Codigo: %s\n\n"
            ,head->nome
            ,head->tipo
            ,head->lab
            ,head->codigo
            );

        }
        head = head->next;
    }
}


//não está sendo usada no momento
/*
void removeNode(struct node **head, char nome[], char lab[]){

    struct node *aux = *head;

    if(strcmp(aux->nome, nome) == 0 && strcmp(aux->lab, lab)==0){
        *head = aux->next;
        free(aux);
    }

    if (aux != NULL) {
        while (aux != NULL) {
            if (strcmp(aux->next->nome, nome) == 0 && strcmp(aux->lab, lab)==0)
            {

            }

        aux = aux->next;
        }
    }
  return NULL;
}
*/

