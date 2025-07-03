#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

Produto* insere_produto(Produto *cabeca, int id, const char *nome, float preco) {
    Produto *novo = malloc(sizeof(Produto));
    if (!novo) return cabeca;
    novo->id = id;
    strncpy(novo->nome, nome, 99);
    novo->nome[99] = '\0';
    novo->preco = preco;
    novo->prox = cabeca;
    return novo;
}

void imprime_lista(Produto *cabeca) {
    Produto *p = cabeca;
    while (p != NULL) {
        printf("ID: %d | Nome: %s | Preço: R$%.2f\n", p->id, p->nome, p->preco);
        p = p->prox;
    }
}

int tamanho_lista(Produto *cabeca) {
    int cont = 0;
    Produto *p = cabeca;
    while (p != NULL) {
        cont++;
        p = p->prox;
    }
    return cont;
}

void libera_lista(Produto *cabeca) {
    Produto *atual = cabeca;
    while (atual != NULL) {
        Produto *prox = atual->prox;
        free(atual);
        atual = prox;
    }
}
