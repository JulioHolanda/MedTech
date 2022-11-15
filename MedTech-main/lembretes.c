#include <stdio.h>
#include <string.h>
#define MAX 100
int main(void) {
  struct horario {
    int hora;
    int minuto;
    int repeticao;
    int hora_prox;
  };
  struct horario tempo, *ptr;
  ptr = &tempo;

  int hor, min, repet, horaprox, quant, cont = 0, quant_remedio, seg = 0;
  int ms = 1;
  char remedio[MAX];
  printf("Digite a quantidade de medicamentos a serem cadastrados: ");
  scanf("%d", &quant);

  for (int i = 0; i < quant; i++) {
    printf("\n----------------------CADASTRO DE "
           "MEDICAMENTO----------------------\n");
    printf("\nDigite o nome do medicamento: ");
    scanf(" %s", remedio);
    printf("\nDigite a hora do remédio: ");
    scanf("%d", &hor);
    printf("\nDigite agora os minutos: ");
    scanf("%d", &min);
    printf("\nDigite agora a quantidade de remédios que serão tomados no "
           "tratamento");
    scanf("%d", &quant_remedio);
    printf("\nDe quanto em quanto tempo (horas) esse medicamento deve ser "
           "ingerido: ");
    scanf("%d", &repet);
    horaprox = hor + repet;

    if (horaprox > 24) {
      horaprox = horaprox - 24;
    }

    ptr->hora = hor;
    ptr->minuto = min;
    ptr->repeticao = repet;
    ptr->hora_prox = horaprox;

    printf("\nO horário mais próximo de tomar %s é às: %d : %d\n", remedio,
           tempo.hora, tempo.minuto);
    printf("\nO proxímo horário será às %d:%d\n", tempo.hora_prox,
           tempo.minuto);
  }
  for (int i = 0; i < quant_remedio; i++) {
    if (seg % 60 == 0) {
      min = ((min + (seg / 60)));
      seg = 0;
    } else {
      if (seg > 60) {
        min = ((min + (seg / 60)));
        seg = ((seg % 60));
      }
    }

    if (min % 60 == 0) {
      hor = ((hor + (min / 60)));
      min = 0;
    } else {
      if (min > 60) {
        hor = ((hor + (min / 60)));
        min = ((min % 60));
      }
    }

    for (seg, hor, min;; seg--) {
      if (hor == 0 && min == 0 && seg == 0) {
        system("clear");
        printf("\nHora de tomar o remédio %s!", remedio);
        system("clear");
        return 0;
      }
      system("clear");
      printf("\n\n%02d:%02d:%02d", hor, min, seg);
      sleep(ms);

      if (seg == 0) {
        min--;
        seg = seg + 60;
      }

      if (min < 0) {
        hor--;
        min = min + 60;
      }
    }
  }

    return 0;
}