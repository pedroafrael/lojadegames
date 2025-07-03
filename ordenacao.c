#include <stdlib.h>
#include "ordenacao.h"

Produto** lista_para_vetor(Produto *cabeca, int n) {
    Produto **v = malloc(n * sizeof(Produto*));
    Produto *p = cabeca;
    for (int i = 0; i < n; i++) {
        v[i] = p;
        p = p->prox;
    }
    return v;
}

static void merge(Produto *v[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    Produto **L = malloc(n1 * sizeof(Produto*));
    Produto **R = malloc(n2 * sizeof(Produto*));
    for (int i = 0; i < n1; i++) L[i] = v[l + i];
    for (int j = 0; j < n2; j++) R[j] = v[m + 1 + j];
    int i=0, j=0, k=l;
    while (i < n1 && j < n2)
        v[k++] = (L[i]->id <= R[j]->id ? L[i++] : R[j++]);
    while (i < n1) v[k++] = L[i++];
    while (j < n2) v[k++] = R[j++];
    free(L); free(R);
}

void mergesort(Produto *v[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergesort(v, l, m);
        mergesort(v, m + 1, r);
        merge(v, l, m, r);
    }
}

int busca_binaria(Produto *v[], int n, int id) {
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (v[m]->id == id) return m;
        else if (v[m]->id < id) l = m + 1;
        else r = m - 1;
    }
    return -1;
}
