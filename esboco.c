#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//aqui vai o rem�dio
struct node{
    char nome[100];
    char princ_ativo[100];
    char tipo[100];
    char ref[100];
    char lab[50];
    char codigo[10];
    struct node *next;
};

char* wordToLower(char string[]);
void insertNode(struct node **head);
void insertFromText(struct node **head, char nome[], char princ[], char tipo[], char ref[], char lab[], char cod[]);
void printando(struct node *head);
void removeNode(struct node **head, char nome[], char lab[]);
void buscaElemento(struct node **head, char nome[], int filtro);
void printSemelhantes(struct node *head, char nome[], int filtro);

int main(){
    FILE *bdd;
    int opt, filtro;
    char remedio[100],nome[100],princ_ativo[100],tipo[100];
    char ref[100],lab[50],codigo[10];

    struct node *head = NULL;
    struct node *novo = NULL;

    bdd = fopen("bdd.txt", "r");

    for(int i=0; i<20; i++){

        fscanf(bdd, " %s %s %s %s %s %s", nome, princ_ativo, tipo, ref, lab, codigo);

        strpcy(nome,wordToLower(nome));strpcy(princ_ativo,wordToLower(princ_ativo));
        strpcy(tipo,wordToLower(tipo));strpcy(ref,wordToLower(ref));
        strpcy(lab,wordToLower(lab));strpcy(codigo,wordToLower(codigo));

        insertFromText(&head, nome, princ_ativo, tipo,ref, lab, codigo);
    }

    fclose(bdd);

    while(1){ //menu interativo
        printf(" --- Que acao voce deseja fazer: ---\n"
               "    1: adicionar remedio\n"
               "    2: consultar por medicamentos\n"
               "    3: consultar por medicamentos COM FILTRO\n"
               "    0: sair:\n");

        scanf(" %d",  &opt);
        printf("\n");

        if ( opt == 1){ //adicionar rem�dio

            insertNode(&head);

        }else if (opt == 2){  //consulta de rem�dios

            printf("Por qual medicamento deseja porcurar?\n");
            scanf(" %[^\n]", &remedio);
            strcpy(remedio,wordToLower(remedio));
            printf("\n");
            buscaElemento(&head, remedio, 0);

        }else if (opt == 3){  //consulta de rem�dios
            do{
                printf("Escolha o tipo de filtro:\n"
                       "1: referencia\n"
                       "2: generico\n"
                       "3: similar\n");
                scanf(" %d", &filtro);
            }while(0 > filtro > 4);

            printf("Por qual medicamento deseja porcurar?\n");
            scanf(" %[^\n]", &remedio);
            printf("\n");
            buscaElemento(&head, remedio, filtro);


        }else if (opt ==0){   // sair do rograma

            break;

        }else { // qualquer outra entrada

            printf(" \n --INSIRA UMA OP��O V�LIDA -- \n");
        }
    }

    return 0;
}

char* wordToLower(char string[]){
    for(int i = 0; string[i]; i++){
        string[i] = tolower(string[i]);
    }
    return string;
}



void insertFromText(struct node **head, char nome[], char princ[], char tipo[], char ref[], char lab[], char cod[]){

    struct node *novo = (struct node*)malloc(sizeof(struct node));
    struct node *aux;

    //caso espa�o criado, preenche dados do node
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

        while(1){ //navegando enquanto lista nao acaba ou fora de posi�ao (alfab�tica)
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

    //caso espa�o criado, preenche dados do node
    if (novo!= NULL){
        printf("Nome: ");
        scanf(" %[^\n]", &novo->nome);
        strpcy(novo->nome,wordToLower(novo->nome));

        printf("Principio ativo: ");
        scanf(" %[^\n]", &novo->princ_ativo);
        strpcy(novo->princ_ativo,wordToLower(novo->princ_ativo));

        printf("Tipo: ");
        scanf(" %[^\n]", &novo->tipo);
        strpcy(novo->tipo,wordToLower(novo->tipo));

        printf("Referencia: ");
        scanf(" %[^\n]", &novo->ref);
        strpcy(novo->ref,wordToLower(novo->ref));

        printf("Laboratorio: ");
        scanf(" %[^\n]", &novo->lab);
        strpcy(novo->lab,wordToLower(novo->lab));

        printf("Codigo de barras: ");
        scanf(" %[^\n]", &novo->codigo);
        strpcy(novo->codigo,wordToLower(novo->codigo));

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

        while(1){ //navegando enquanto lista nao acaba ou fora de posi�ao (alfab�tica)
            if(aux->next == NULL ||strcmp(novo->nome,aux->next->nome)<=0){
                novo->next = aux->next;
                aux->next = novo;
                break;
            }
            aux=aux->next;
        }
    }
}

void buscaElemento(struct node **head, char nome[], int filtro){
    struct node *aux = *head;
    char igual[100];

    if (*head != NULL) {
        while (aux != NULL) {
            if (strcmp(aux->nome, nome) == 0){  //se remedio encontrado na lista
                strcpy(igual, aux->princ_ativo);
                printSemelhantes(*head, igual, filtro);  //imprime remedios de mesmo princp ativo
                break;
            }
        aux = aux->next;
        }
    }
  return NULL;
}

void printSemelhantes(struct node *head, char nome[], int filtro){ //print de remedios semelhantes
    char *opcoesFiltro[] = {" ","referencia","generico","similar"};

    if(filtro == 0 ){
        while (head != NULL){
            if (strcmp(head->princ_ativo, nome) == 0){ //se de mesmo principio ativo, � printado

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
    }else{
        while (head != NULL){
            if (strcmp(head->princ_ativo, nome) == 0 && strcmp(head->tipo, opcoesFiltro[filtro]) == 0 ){ //se de mesmo principio ativo E dentro do filtro, � printado

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
        }}
}


//n�o est� sendo usada no momento
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

