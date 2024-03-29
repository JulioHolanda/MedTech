#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main(void) {

  struct tm *data_hora_atual;

  time_t segundos;

  time(&segundos);
  data_hora_atual = localtime(&segundos);


  int hor, min;
  float intervalo;
  int ms=30;//30 é o valor equivalente a 1 minuto. Para fins de teste mais rápido, este valor pode ser alterado para 1, fazendo o loop rodar de 1 em 1 segundo.
  int quant_remedio, dose_remedio;
  int pastTime=0, tomados=0, intervaloINT;

  printf("\n\nVamos marcar o intervalo de tempo que será preciso no tratamento!");

  printf("\n\nDe quantas em quantas horas precisará tomar o remédio? ");
  printf("\nDigite aqui:");
  scanf("%f", &intervalo);

  printf("\n\nDigite a quantidade(total) de remédios(comprimidos, copinhos) que precisará tomar:");
  scanf("%d", &quant_remedio);
  printf("\n\nDigite a dose de remédios que terá de tomar a cada chamada:");
  scanf("%d", &dose_remedio);

  intervalo = 60*intervalo;

  intervaloINT = (int)intervalo;

  printf(" %d", intervaloINT);

  hor=data_hora_atual->tm_hour;
  min=data_hora_atual->tm_min;

  system("clear");
  printf("\nHora atual ........: %02d:%02d",hor, min);//hora e minuto atual

  if (min % 60 == 0) {
    hor = ((hor + (min / 60)));
    min = 0;
  } else {
    if (min > 60) {
      hor = ((hor + (min / 60)));
      min = ((min % 60));
    }
  }

  while(1){

    min+=1;//Para fins de teste, este valor do min+=1 poderá ser mudado.  A equipe recomenda que o valor seja alterado para: 10, 20 ou 30.

    pastTime += 1;//Para fins de teste, este valor do pastTime+=1 poderá ser mudado. O valor de "pastTime" deverá ser o mesmo de "min".
    if (min >= 60){
        min = min - 60;
        hor++;
        if(hor==24){
            hor=00;
        }
    }
    system("clear");
    printf("\n\nHora atual ........: %02d:%02d", hor, min);
    sleep(ms);

    if (pastTime >= intervaloINT) {
      system("clear");
      printf("\n\nHora de tomar o remédio!");
      pastTime = 0;
      tomados += dose_remedio;

      if(tomados == quant_remedio){
        printf("\n - Fim do tratamento - \n");
        exit(0);
      }
    }
    sleep(ms);

    }

  return 0;
}
