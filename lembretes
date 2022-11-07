#include <stdio.h>
#include <string.h>
#define MAX 100
int main(void) {
  struct horario{
    int hora;
    int minuto;
    int repeticao;
    int hora_prox;
  };
  struct horario tempo, *ptr;
  ptr=&tempo;

  int hr, min, repet, horaprox, quant;
  char remedio[MAX];
  printf("Digite a quantidade de medicamentos a serem cadastrados: ");
  scanf("%d", &quant);

  for (int i=0; i<quant; i++){
    printf("\n----------------------CADASTRO DE MEDICAMENTO----------------------\n");
    printf("\nDigite o nome do medicamento: ");
    scanf(" %s", remedio);
    printf("\nDigite a hora do remédio: ");
    scanf("%d", &hr);
    printf("\nDigite agora os minutos: ");
    scanf("%d", &min);
    printf("\nDe quanto em quanto tempo (horas) esse medicamento deve ser ingerido: ");
    scanf("%d", &repet);
    horaprox=hr+repet;

    if (horaprox>24){
      horaprox=horaprox-24;
    }
    
    ptr -> hora = hr;
    ptr -> minuto = min;
    ptr -> repeticao = repet;
    ptr -> hora_prox = horaprox;
  
    printf("\nO horário mais próximo de tomar %s é às: %d : %d\n", medicamento, tempo.hora, tempo.minuto);
    printf("\nO proxímo horário será às %d:%d\n", tempo.hora_prox, tempo.minuto);
 
  }
  
  return 0;

}
