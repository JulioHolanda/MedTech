#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ADMIN 0

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
void removeNode(struct node **head, char nome[], char lab[]);
void buscaElemento(struct node **head, char nome[], int filtro);
void printSemelhantes(struct node **head, char nome[], int filtro);
void removeNode(struct node **head, char nome[], char lab[]);

//PARA TESTES
/*
void printando(struct node *head){
 int i =2;
    if (head == NULL){
        printf("lista vazia");
    }else{
        printf(" -Nome: %s\n"
                "  princp: %s\n"
                "  Tipo: %s\n\n"
                ,head->nome
                ,head->princ_ativo
                ,head->tipo
                );
        head = head->next;
        while (head != NULL){
            printf(" - %d Nome: %s\n"
                "  princp: %s\n"
                "  Tipo: %s\n\n"
                ,i
                ,head->nome
                ,head->princ_ativo
                ,head->tipo
                );
            head = head->next;
            i++;
        }
        printf("\n");
    }
}
*/

int main(){
    FILE *bdd;
    int opt, filtro;
    char remedio[100],nome[100],princ_ativo[100],tipo[100];
    char ref[100],lab[50],codigo[10];

    struct node *head = NULL;


    bdd = fopen("bdd.txt", "r");

    for(int i=0; i<20; i++){

        fscanf(bdd, " %s %s %s %s %s %s", nome, princ_ativo, tipo, ref, lab, codigo);

        strcpy(nome,wordToLower(nome));strcpy(princ_ativo,wordToLower(princ_ativo));
        strcpy(tipo,wordToLower(tipo));strcpy(ref,wordToLower(ref));
        strcpy(lab,wordToLower(lab));strcpy(codigo,wordToLower(codigo));

        insertFromText(&head, nome, princ_ativo, tipo,ref, lab, codigo);
    }

    fclose(bdd);

    //PARA TESTES
    //printando(head);
    #if ADMIN == 1
        printf("\n --- VERSAO ADMIN --- \n");

        printf("\n --- Bem vindo(a) ao PIU --- \n\n");

        while(1){ //menu interativo
            printf(" --- Que acao voce deseja fazer: ---\n"
                   "    1: adicionar remedio\n"
                   "    2: deletar remedio\n"
                   "    3: consultar por medicamentos\n"
                   "    4: consultar por medicamentos COM FILTRO\n"
                   "    0: sair:\n ");

            scanf(" %d",  &opt);
            printf("\n");

            if ( opt == 1){ //adicionar rem�dio

                printf(" -- ADICIONAR --\n");
                insertNode(&head);

            }else if (opt == 2){ //deletar rem�dio

                printf(" -- DELETAR --\n");
                printf(" Nome: ");
                scanf(" %[^\n]", &remedio);
                printf(" Laboratorio: ");
                scanf(" %[^\n]", &lab);

                removeNode(&head, remedio, lab);

                    //PARA TESTES
                //printando(head);


            }else if (opt == 3){  //consulta de rem�dios

                printf(" Por qual medicamento deseja porcurar?\n ");
                scanf(" %[^\n]", &remedio);
                strcpy(remedio,wordToLower(remedio));
                printf("\n");
                buscaElemento(&head, remedio, 0);

            }else if (opt == 4){  //consulta de rem�dios filtrado
                do{
                    printf(" Escolha o tipo de filtro:\n"
                           "    1: referencia\n"
                           "    2: generico\n"
                           "    3: similar\n ");
                    scanf(" %d", &filtro);
                }while(0 > filtro > 4);

                printf(" Por qual medicamento deseja porcurar?\n ");

                scanf(" %[^\n]", &remedio);
                printf("\n");
                buscaElemento(&head, remedio, filtro);


            }else if (opt ==0){   // sair do rograma
                printf("\n -- FIM -- \n");
                break;

            }else { // qualquer outra entrada

                printf(" \n --INSIRA UMA OP��O V�LIDA -- \n");
            }
        }
    #else
        printf("\n --- Bem vindo(a) ao PIU --- \n\n");

        while(1){ //menu interativo
            printf(" --- Que acao voce deseja fazer: ---\n"
                   "    1: consultar por medicamentos\n"
                   "    2: consultar por medicamentos COM FILTRO\n"
                   "    0: sair:\n ");

            scanf(" %d",  &opt);
            printf("\n");

            if (opt == 1){  //consulta de rem�dios

                printf(" Por qual medicamento deseja porcurar?\n ");
                scanf(" %[^\n]", &remedio);
                strcpy(remedio,wordToLower(remedio));
                printf("\n");
                buscaElemento(&head, remedio, 0);

            }else if (opt == 2){  //consulta de rem�dios filrado
                do{
                    printf(" Escolha o tipo de filtro:\n"
                           "    1: referencia\n"
                           "    2: generico\n"
                           "    3: similar\n ");
                    scanf(" %d", &filtro);
                }while(0 > filtro > 4);

                printf(" Por qual medicamento deseja porcurar?\n ");

                scanf(" %[^\n]", &remedio);
                printf("\n");
                buscaElemento(&head, remedio, filtro);


            }else if (opt ==0){   // sair do rograma
                printf("\n -- FIM -- \n");
                break;

            }else { // qualquer outra entrada

                printf(" \n --INSIRA UMA OP��O V�LIDA -- \n");
            }
        }
    #endif // ADMIN

    free(head);

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
    aux = *head;

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

    }else if(strcmp(novo->princ_ativo,(*head)->princ_ativo)<0){ //antes do head
            novo->next = *head;
            *head= novo;

    }else if(strcmp(novo->princ_ativo,(*head)->princ_ativo)==0){ //semelhante ao head

        if(strcmp(novo->nome,(*head)->nome)<0){ // e antes do head
            novo->next = *head;
            *head= novo;

        }else if(strcmp(novo->nome,(*head)->nome)==0){ //semelhante ao head
            novo->next = (*head)->next;
            (*head)->next = novo;
        }else{
            while(aux->next != NULL && strcmp(novo->nome,aux->next->nome)>0 && strcmp(novo->princ_ativo,aux->next->princ_ativo)==0){
                aux=aux->next;
            }

            if(aux->next == NULL){
                novo->next = NULL;
                aux->next = novo;

            }else{
                novo->next = aux->next;
                aux->next = novo;
            }
        }

    }else{
        while(aux->next != NULL && strcmp(novo->princ_ativo,aux->next->princ_ativo)>0){ //navegando enquanto lista nao acaba ou fora de posi�ao (alfab�tica -> principios ativos)
            aux=aux->next;
        }

        if(aux->next == NULL){
            novo->next = NULL;
            aux->next = novo;

        }else if(strcmp(novo->princ_ativo,aux->next->princ_ativo)==0){
                while (aux->next != NULL && strcmp(novo->nome,aux->next->nome)>0 && strcmp(novo->princ_ativo,aux->next->princ_ativo)==0){  //navegando enquanto lista nao acaba ou fora de posi�ao (alfab�tica -> nome, dentro do mesmo principio ativo)
                    aux=aux->next;
                }

                if(aux->next == NULL){
                    novo->next = NULL;
                    aux->next = novo;

                }else{
                    novo->next = aux->next;
                    aux->next = novo;
                }
        }else{
            novo->next = aux->next;
            aux->next = novo;
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
        strcpy(novo->nome,wordToLower(novo->nome));

        printf("Principio ativo: ");
        scanf(" %[^\n]", &novo->princ_ativo);
        strcpy(novo->princ_ativo,wordToLower(novo->princ_ativo));

        printf("Tipo: ");
        scanf(" %[^\n]", &novo->tipo);
        strcpy(novo->tipo,wordToLower(novo->tipo));

        printf("Referencia: ");
        scanf(" %[^\n]", &novo->ref);
        strcpy(novo->ref,wordToLower(novo->ref));

        printf("Laboratorio: ");
        scanf(" %[^\n]", &novo->lab);
        strcpy(novo->lab,wordToLower(novo->lab));

        printf("Codigo de barras: ");
        scanf(" %[^\n]", &novo->codigo);
        strcpy(novo->codigo,wordToLower(novo->codigo));

    }
    if((*head)==NULL){  //ta vazia
        (*head)=novo;
        (*head)->next = NULL;

    }else if(strcmp(novo->princ_ativo,(*head)->princ_ativo)<0){ //antes do head
            novo->next = *head;
            *head= novo;

    }else if(strcmp(novo->princ_ativo,(*head)->princ_ativo)==0){ //semelhante ao head

        if(strcmp(novo->nome,(*head)->nome)<0){ // e antes do head
            novo->next = *head;
            *head= novo;

        }else if(strcmp(novo->nome,(*head)->nome)==0){ //semelhante ao head
            novo->next = (*head)->next;
            (*head)->next = novo;
        }else{
            while(aux->next != NULL && strcmp(novo->nome,aux->next->nome)>0 && strcmp(novo->princ_ativo,aux->next->princ_ativo)==0){
                aux=aux->next;
            }

            if(aux->next == NULL){
                novo->next = NULL;
                aux->next = novo;

            }else{
                novo->next = aux->next;
                aux->next = novo;
            }
        }

    }else{
        while(aux->next != NULL && strcmp(novo->princ_ativo,aux->next->princ_ativo)>0){ //navegando enquanto lista nao acaba ou fora de posi�ao (alfab�tica -> principios ativos)
            aux=aux->next;
        }

        if(aux->next == NULL){
            novo->next = NULL;
            aux->next = novo;

        }else if(strcmp(novo->princ_ativo,aux->next->princ_ativo)==0){
                while (aux->next != NULL && strcmp(novo->nome,aux->next->nome)>0 && strcmp(novo->princ_ativo,aux->next->princ_ativo)==0){  //navegando enquanto lista nao acaba ou fora de posi�ao (alfab�tica -> nome, dentro do mesmo principio ativo)
                    aux=aux->next;
                }

                if(aux->next == NULL){
                    novo->next = NULL;
                    aux->next = novo;

                }else{
                    novo->next = aux->next;
                    aux->next = novo;
                }
        }else{
            novo->next = aux->next;
            aux->next = novo;
        }
    }
}

void buscaElemento(struct node **head, char nome[], int filtro){
    struct node *aux = *head;
    char igual[100];
    int encontrado = 0;

    if (*head != NULL) {
        while (aux != NULL) {
            if (strcmp(aux->nome, nome) == 0){  //se remedio encontrado na lista
                strcpy(igual, aux->princ_ativo);
                printSemelhantes(head, igual, filtro);  //imprime remedios de mesmo princp ativo
                encontrado = 1;
                break;
            }
        aux = aux->next;
        }
    }
    if (encontrado == 0){
        printf("  - medicamento NAO encontrado - \n\n");
    }
  return NULL;
}

void printSemelhantes(struct node **head, char nome[], int filtro){ //print de remedios semelhantes
    char *opcoesFiltro[] = {" ","referencia","generico","similar"};
    struct node *aux;
    aux = *head;

    if(filtro == 0 ){
        struct node *referencia;
        struct node *generico;
        struct node *similar;

        while(aux != NULL && strcmp(aux->princ_ativo, nome) != 0){
            aux = aux->next;
        }

        //grupo encontrado
        referencia = aux;
        generico = aux;
        similar = aux;

        while(referencia != NULL && strcmp(referencia->princ_ativo, nome) == 0){
            if(strcmp(referencia->tipo, "referencia")==0){
                printf(" -Nome: %s\n"
                "  Tipo: %s\n"
                "  Laboratorio: %s\n"
                "  Codigo: %s\n\n"
                ,referencia->nome
                ,referencia->tipo
                ,referencia->lab
                ,referencia->codigo
                );
            }
            referencia = referencia->next;
        }
        while(generico != NULL  && strcmp(generico->princ_ativo, nome) == 0 ){
            if(strcmp(generico->tipo, "generico")==0){
                printf(" -Nome: %s\n"
                "  Tipo: %s\n"
                "  Laboratorio: %s\n"
                "  Codigo: %s\n\n"
                ,generico->nome
                ,generico->tipo
                ,generico->lab
                ,generico->codigo
                );
            }
            generico = generico->next;
        }
        while(similar != NULL && strcmp(similar->princ_ativo, nome) == 0){
            if(strcmp(similar->tipo, "similar")==0 ){
                printf(" -Nome: %s\n"
                "  Tipo: %s\n"
                "  Laboratorio: %s\n"
                "  Codigo: %s\n\n"
                ,similar->nome
                ,similar->tipo
                ,similar->lab
                ,similar->codigo
                );

            }
            similar = similar->next;
        }
    }else{
        while(aux != NULL && strcmp(aux->princ_ativo, nome) != 0){
            aux = aux->next;
        }

        while (aux != NULL && strcmp(aux->princ_ativo, nome) == 0){
            if ( strcmp(aux->tipo, opcoesFiltro[filtro]) == 0 ){ //se de mesmo principio ativo E dentro do filtro, � printado

                printf(" -Nome: %s\n"
                "  Tipo: %s\n"
                "  Laboratorio: %s\n"
                "  Codigo: %s\n\n"
                ,aux->nome
                ,aux->tipo
                ,aux->lab
                ,aux->codigo
                );

            }
            aux = aux->next;
        }}
}


void removeNode(struct node **head, char nome[], char lab[]){

    struct node *aux = *head;
    struct node *temp;
    int deletado = 0;

    if (strcmp((*head)->nome, nome) == 0 && strcmp((*head)->lab, lab)==0){
        temp = (*head);
        (*head) = (*head)->next;

        deletado = 1;
        printf("  - medicamento DELETADO com sucesso - \n\n");


    }else if (aux != NULL) {
        while (aux->next != NULL) {
            if (strcmp(aux->next->nome, nome) == 0 && strcmp(aux->next->lab, lab)==0){
                temp = aux->next;
                aux->next = aux->next->next;

                deletado = 1;
                printf("  - medicamento DELETADO com sucesso - \n\n");

                break;
            }

            aux = aux->next;
        }
    }
    if (deletado == 0){
        printf("  - medicamento ou semelhantes NAO encontrados - \n\n");
    }
    free(temp);
}
