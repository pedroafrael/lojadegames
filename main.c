#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "ordenacao.h"
// inclua seus headers login.h, game.h...

int main() {
    Produto *lista = NULL;
    int opc, id, encontrou;
    char nome[100];
    float preco;

    do {
        printf("\n=== LOJA DE GAMES ===\n1 Cadastrar produto\n2 Listar produtos\n3 Ordenar por ID e buscar\n0 Sair\nOpção: ");
        scanf("%d", &opc);
        switch (opc) {
            case 1:
                printf("ID: "); scanf("%d", &id);
                printf("Nome: "); getchar(); fgets(nome, 100, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("Preço: "); scanf("%f", &preco);
                lista = insere_produto(lista, id, nome, preco);
                break;
            case 2:
                imprime_lista(lista);
                break;
            case 3: {
                int n = tamanho_lista(lista);
                if (n <= 0) {
                    printf("Nenhum produto cadastrado.\n");
                    break;
                }
                Produto **vet = lista_para_vetor(lista, n);
                mergesort(vet, 0, n - 1);
                printf("Informe o ID a buscar: "); scanf("%d", &id);
                encontrou = busca_binaria(vet, n, id);
                if (encontrou >= 0) {
                    Produto *p = vet[encontrou];
                    printf("Produto encontrado!\nID: %d | Nome: %s | Preço: R$%.2f\n", p->id, p->nome, p->preco);
                } else printf("Produto com ID %d não encontrado.\n", id);
                free(vet);
                break;
            }
            case 0:
                libera_lista(lista);
                printf("Saindo...Volte sempre!\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opc != 0);

    return 0;
}
