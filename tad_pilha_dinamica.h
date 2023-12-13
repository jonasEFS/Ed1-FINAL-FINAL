#ifndef TAD_PILHA_DINAMICA_H
#define TAD_PILHA_DINAMICA_H

//#include "biblioteca.h"
// nao precisa?
//
#include <stdio.h>
#include <cstdlib>

struct T_Item {
  int campo;
  int flagZeroIntUmChar;
};

struct T_No {
  T_Item item;
  T_No *prox;
};

struct T_Pilha {
  T_No *topo;
  int qtdeAtual;
};

void iniciarPilha(T_Pilha *pilha) {
  (*pilha).topo = NULL;
  (*pilha).qtdeAtual = 0;
}

int chkPilhaVazia(T_Pilha *pilha) { return (*pilha).topo == NULL; }

void inserir(T_Pilha *pilha, T_Item item) {
  T_No *novoNo = (T_No *)malloc(sizeof(T_No));
  novoNo->item = item;
  novoNo->prox = (*pilha).topo;
  (*pilha).topo = novoNo;
  (*pilha).qtdeAtual++;
}

int remover(T_Pilha *pilha) {
  if (chkPilhaVazia(pilha))
    return 0;

  T_No *noRemovido = (*pilha).topo;
  (*pilha).topo = noRemovido->prox;
  free(noRemovido);
  (*pilha).qtdeAtual--;

  return 1;
}

void liberarPilha(T_Pilha *pilha) {
  while (remover(pilha))
    ;
}
const int max = 99;

#endif
