#include <stdio.h>
#include <string.h>
#include "login.h"
#include "game.h"
#include "utils.h"

int main() {
    if (!login()) {
        return 0;
    }

    printf("\\n--- Bem-vindo à Loja de Games do Pedro! ---\\n");

    int opcao;
    do {
        printf("\\nMenu:\\n");
        printf("1 - Cadastrar Game\\n");
        printf("2 - Listar Games\\n");
        printf("3 - Editar Game\\n");
        printf("4 - Excluir Game\\n");
        printf("5 - Buscar Game por Codigo\\n");
        printf("6 - Listar Games em Promocao\\n");
        printf("7 - Listar Games por Genero\\n");
        printf("8 - Ordenar Games por Preco\\n");
        printf("9 - Sair\\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        limparBuffer();

        switch (opcao) {
            case 1:
                cadastrarGame();
                break;
            case 2:
                listarGames();
                break;
            case 3:
                editarGame();
                break;
            case 4:
                excluirGame();
                break;
            case 5: {
                int codigo;
                printf("Digite o codigo do game: ");
                scanf("%d", &codigo);
                limparBuffer();
                buscarGame(codigo);
                break;
            }
            case 6:
                listarGamesPromocao();
                break;
            case 7: {
                char genero[50];
                printf("Digite o genero: ");
                fgets(genero, sizeof(genero), stdin);
                genero[strcspn(genero, "\\n")] = 0;
                listarGamesGenero(genero);
                break;
            }
            case 8:
                ordenarGamesPreco();
                break;
            case 9:
                printf("Saindo...\\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\\n");
        }
    } while (opcao != 9);

    return 0;
}
