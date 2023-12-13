#ifndef MINHASFUNCOES_H
#define MINHASFUNCOES_H

#include "tad_pilha_dinamica.h"
#include <cstdlib>
#include <cstring>
#include <ctype.h>

void listar_pilha(T_Pilha *pilhaExpressao) {
  T_No *aux = pilhaExpressao->topo;

  while (aux != NULL) {
    if (aux->item.flagZeroIntUmChar == 0) {
      printf("%d ", aux->item.campo);
    } else {
      printf("%c ", aux->item.campo);
    }
    aux = aux->prox;
  }
  printf("\n");
}

int meuDesempilhar(T_Pilha *pilha) {
  if (chkPilhaVazia(pilha))
    return 0;

  int aDesempilhar = pilha->topo->item.campo;

  T_No *noRemovido = pilha->topo;
  pilha->topo = noRemovido->prox;
  free(noRemovido);
  pilha->qtdeAtual--;

  return aDesempilhar;
}

void calcular_resultado(T_Pilha *pilhaExpressao, T_Pilha *pilhaResultado) {
  T_No *aux = pilhaExpressao->topo;

  while (aux != NULL) {
    T_Item *aSerTestado = &(aux->item);

    if (aSerTestado->flagZeroIntUmChar == 0) {
      int value = aSerTestado->campo;
      T_Item item;
      item.campo = value;
      inserir(pilhaResultado, item);
    } else {
      int operador1 = meuDesempilhar(pilhaResultado);
      int operador2 = meuDesempilhar(pilhaResultado);
      int resultado;

      switch (aSerTestado->campo) {
      case '+':
        resultado = operador2 + operador1;
        break;
      case '-':
        resultado = operador2 - operador1;
        break;
      case '*':
        resultado = operador2 * operador1;
        break;
      case '/':
        resultado = operador2 / operador1;
        break;
      }

      T_Item resultadoItem;
      resultadoItem.campo = resultado;
      inserir(pilhaResultado, resultadoItem);
    }

    aux = aux->prox;
  }
}

void meuGerarPosfixa(T_Pilha *plOutput, char exp[], int capacidade) {
  T_Pilha plOperadores;
  T_Pilha plTemp;
  iniciarPilha(&plOperadores);
  iniciarPilha(&plTemp);

  T_Item item;

  int i = 0;
  while (exp[i] != '\0') {
    if (isdigit(exp[i])) {
      int num = 0;
      while (isdigit(exp[i])) {
        num = num * 10 + (exp[i] - '0');
        i++;
      }

      item.campo = num;
      item.flagZeroIntUmChar = 0;
      inserir(&plTemp, item);
    } else if (strchr("+-*/", exp[i]) != NULL) {
      item.campo = exp[i];
      item.flagZeroIntUmChar = 1;

      while (!chkPilhaVazia(&plOperadores) &&
             plOperadores.topo->item.campo != '(') {
        inserir(&plTemp, plOperadores.topo->item);
        remover(&plOperadores);
      }

      inserir(&plOperadores, item);
      i++;
    } else if (exp[i] == '(') {
      item.campo = '(';
      item.flagZeroIntUmChar = 1;
      inserir(&plOperadores, item);
      i++;
    } else if (exp[i] == ')') {
      while (!chkPilhaVazia(&plOperadores) &&
             plOperadores.topo->item.campo != '(') {
        inserir(&plTemp, plOperadores.topo->item);
        remover(&plOperadores);
      }

      remover(&plOperadores);
      i++;
    } else {
      i++;
    }
  }

  while (!chkPilhaVazia(&plOperadores)) {
    inserir(&plTemp, plOperadores.topo->item);
    remover(&plOperadores);
  }

  while (!chkPilhaVazia(&plTemp)) {
    inserir(plOutput, plTemp.topo->item);
    remover(&plTemp);
  }
}

#endif
