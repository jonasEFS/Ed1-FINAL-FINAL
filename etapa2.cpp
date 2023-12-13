#include "minhasfuncoes.h",
#include "tad_pilha_dinamica.h"
#include <stdio.h>

int main(void) {
  char expressao[max];
  scanf("%s", expressao);

  T_Pilha pilhaExpressao;
  iniciarPilha(&pilhaExpressao);

  meuGerarPosfixa(&pilhaExpressao, expressao, max);
  listar_pilha(&pilhaExpressao);

  T_Pilha pilhaResultado;
  iniciarPilha(&pilhaResultado);
  calcular_resultado(&pilhaExpressao, &pilhaResultado);

  printf("%d ", pilhaResultado.topo->item.campo);
  printf("\n");

  liberarPilha(&pilhaExpressao);
  liberarPilha(&pilhaResultado);

  return 0;
}

