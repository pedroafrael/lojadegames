#ifndef LISTA_H
#define LISTA_H

typedef struct Produto {
    int id;
    char nome[100];
    float preco;
    struct Produto *prox;
} Produto;

Produto* insere_produto(Produto *cabeca, int id, const char *nome, float preco);
void imprime_lista(Produto *cabeca);
int tamanho_lista(Produto *cabeca);
void libera_lista(Produto *cabeca);

#endif
