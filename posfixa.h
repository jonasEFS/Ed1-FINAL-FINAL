#ifndef POSFIXA_H
#define POSFIXA_H

#include "tad_pilha_estatica.h"
#include <string.h>

enum Operacoes { MULT = '*', SOMA = '+', SUB = '-', DIV = '/' };

void gerar_posfixa(T_Pilha *plOutput, char exp[]) {

  T_Pilha plOperadores;
  iniciarPilha(&plOperadores);

  T_Item item;

  for (int i = 0; i < strlen(exp); i++) {

    item.campo = exp[i];

    switch (exp[i]) {

    case '0' ... '9':
      inserir(plOutput, item);
      break;

    case MULT ... DIV:
      inserir(&plOperadores, item);
      break;

    case ')': {
      inserir(plOutput, plOperadores.dados[plOperadores.topo - 1]);
      remover(&plOperadores);
      break;
    }
    }
  }
}

#endif
