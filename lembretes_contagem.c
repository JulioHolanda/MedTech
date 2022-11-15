#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <unistd.h>

int main() {

  int hor, min;
  float intervalo, ms =1.0;
  int quant_remedio, dose_remedio;
  int pastTime=0, tomados=0, intervaloINT;

  printf("\n\nVamos marcar o intervalo de tempo que ser� preciso no tratamento!");
  printf("\n\nDigite o n�mero de horas: ");
  scanf("%d", &hor);
  printf("\n\nDigite o n�mero de minutos: ");
  scanf("%d", &min);
  printf("\n\nDe quantas em quantas horas precisar� tomar o rem�dio (em horas): ");
  scanf("%f", &intervalo);
  printf("\n\nDigite a quantidade (total) de rem�dios que ter� de tomar:");
  scanf("%d", &quant_remedio);
  printf("\n\nDigite a dose de rem�dios que ter� de tomar a cada chamada:");
  scanf("%d", &dose_remedio);

  intervalo = 60*intervalo;

  intervaloINT = (int)intervalo;

printf(" %d", intervaloINT);

  //----------------------------Se o usu�rio digitar um valor acima de 60
  // para
  // os minutos, este ser� enviado para as horas transformando-a em valor
  // equivalente-------------
  if (min % 60 == 0) {
    hor = ((hor + (min / 60)));
    min = 0;
  } else {
    if (min > 60) {
      hor = ((hor + (min / 60)));
      min = ((min % 60));
    }
  }

   // In�cio do c�digo do cronometro
  printf("\n\n%02d:%02d", hor, min);
  sleep(ms);

  while(1){

    min+=10;
    pastTime += 10;
    if (min >= 60){
        min = min - 60;
        hor++;
        if(hor==24){
            hor=00;
        }
    }
    printf("\n\n%02d:%02d", hor, min);

    if (pastTime >= intervaloINT) {
      //system("clear");
      printf("\nHora de tomar o rem�dio!");
      //system("clear");
      pastTime = 0;
      tomados += dose_remedio;

      if(tomados == quant_remedio){
        printf("\n - Fim do alarme - \n");
        exit(0);
      }
    }
    //system("clear");
    sleep(ms);

    }
    /* -------- Quando (minutos) chega a 60 incrementamos +1 para (horas) e
     * zera a parte dos minutos ----------- */



  /* ---------------------------------------------------------------------------
   * Fim do c�digo do cronometro
   * ------------------------------------------------------------------ */

  return 0;
}
