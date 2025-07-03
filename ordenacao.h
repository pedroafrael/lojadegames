#ifndef ORDENACAO_H
#define ORDENACAO_H

#include "lista.h"

Produto** lista_para_vetor(Produto *cabeca, int n);
void mergesort(Produto *v[], int l, int r);
int busca_binaria(Produto *v[], int n, int id);

#endif // ORDENACAO_H
