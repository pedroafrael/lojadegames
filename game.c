#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

#define ARQUIVO "games.txt"

void carregarGames(Game **games, int *qtd) {
    FILE *fp = fopen(ARQUIVO, "r");
    if (!fp) {
        *games = NULL;
        *qtd = 0;
        return;
    }

    int capacidade = 10;
    *games = malloc(sizeof(Game) * capacidade);
    *qtd = 0;

    while (fscanf(fp, "%d;%[^;];%[^;];%f;%d\\n",
                  &(*games)[*qtd].codigo,
                  (*games)[*qtd].nome,
                  (*games)[*qtd].genero,
                  &(*games)[*qtd].preco,
                  &(*games)[*qtd].promocao) == 5) {
        (*qtd)++;
        if (*qtd >= capacidade) {
            capacidade *= 2;
            *games = realloc(*games, sizeof(Game) * capacidade);
        }
    }
    fclose(fp);
}

void salvarGames(Game *games, int qtd) {
    FILE *fp = fopen(ARQUIVO, "w");
    if (!fp) {
        printf("Erro ao salvar dados.\\n");
        return;
    }
    for (int i = 0; i < qtd; i++) {
        fprintf(fp, "%d;%s;%s;%.2f;%d\\n",
                games[i].codigo,
                games[i].nome,
                games[i].genero,
                games[i].preco,
                games[i].promocao);
    }
    fclose(fp);
}

void cadastrarGame() {
    Game novo;
    Game *games = NULL;
    int qtd = 0;

    carregarGames(&games, &qtd);

    printf("Digite o codigo do game: ");
    scanf("%d", &novo.codigo);
    getchar();

    for (int i = 0; i < qtd; i++) {
        if (games[i].codigo == novo.codigo) {
            printf("Codigo ja existe. Cadastro cancelado.\\n");
            free(games);
            return;
        }
    }

    printf("Nome do game: ");
    fgets(novo.nome, MAX_NOME, stdin);
    novo.nome[strcspn(novo.nome, "\\n")] = 0;

    printf("Genero do game: ");
    fgets(novo.genero, MAX_GENERO, stdin);
    novo.genero[strcspn(novo.genero, "\\n")] = 0;

    printf("Preco do game: ");
    scanf("%f", &novo.preco);

    printf("Esta em promocao? (1-sim, 0-nao): ");
    scanf("%d", &novo.promocao);

    games = realloc(games, sizeof(Game) * (qtd + 1));
    games[qtd] = novo;
    qtd++;

    salvarGames(games, qtd);
    free(games);
    printf("Game cadastrado com sucesso!\\n");
}

void listarGames() {
    Game *games = NULL;
    int qtd = 0;

    carregarGames(&games, &qtd);

    if (qtd == 0) {
        printf("Nenhum game cadastrado.\\n");
        return;
    }

    printf("Lista de Games:\\n");
    printf("Codigo | Nome | Genero | Preco | Promocao\\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d | %s | %s | %.2f | %s\\n",
               games[i].codigo,
               games[i].nome,
               games[i].genero,
               games[i].preco,
               games[i].promocao ? "Sim" : "Nao");
    }
    free(games);
}

void editarGame() {
    Game *games = NULL;
    int qtd = 0;
    int codigo;

    carregarGames(&games, &qtd);

    if (qtd == 0) {
        printf("Nenhum game cadastrado.\\n");
        return;
    }

    printf("Digite o codigo do game para editar: ");
    scanf("%d", &codigo);
    getchar();

    int achou = 0;
    for (int i = 0; i < qtd; i++) {
        if (games[i].codigo == codigo) {
            achou = 1;

            printf("Nome atual: %s\\n", games[i].nome);
            printf("Novo nome: ");
            fgets(games[i].nome, MAX_NOME, stdin);
            games[i].nome[strcspn(games[i].nome, "\\n")] = 0;

            printf("Genero atual: %s\\n", games[i].genero);
            printf("Novo genero: ");
            fgets(games[i].genero, MAX_GENERO, stdin);
            games[i].genero[strcspn(games[i].genero, "\\n")] = 0;

            printf("Preco atual: %.2f\\n", games[i].preco);
            printf("Novo preco: ");
            scanf("%f", &games[i].preco);

            printf("Promocao atual: %s\\n", games[i].promocao ? "Sim" : "Nao");
            printf("Novo status promocao (1-sim, 0-nao): ");
            scanf("%d", &games[i].promocao);

            salvarGames(games, qtd);
            printf("Game editado com sucesso!\\n");
            break;
        }
    }
    if (!achou) {
        printf("Game nao encontrado.\\n");
    }
    free(games);
}

void excluirGame() {
    Game *games = NULL;
    int qtd = 0;
    int codigo;

    carregarGames(&games, &qtd);

    if (qtd == 0) {
        printf("Nenhum game cadastrado.\\n");
        return;
    }

    printf("Digite o codigo do game para excluir: ");
    scanf("%d", &codigo);

    int achou = 0;
    for (int i = 0; i < qtd; i++) {
        if (games[i].codigo == codigo) {
            achou = 1;
            for (int j = i; j < qtd -1; j++) {
                games[j] = games[j+1];
            }
            qtd--;
            salvarGames(games, qtd);
            printf("Game excluido com sucesso!\\n");
            break;
        }
    }
    if (!achou) {
        printf("Game nao encontrado.\\n");
    }
    free(games);
}

void quicksortPreco(Game *arr, int left, int right) {
    int i = left, j = right;
    Game tmp;
    float pivot = arr[(left + right)/2].preco;

    while (i <= j) {
        while (arr[i].preco < pivot) i++;
        while (arr[j].preco > pivot) j--;

        if (i <= j) {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++; j--;
        }
    }
    if (left < j) quicksortPreco(arr, left, j);
    if (i < right) quicksortPreco(arr, i, right);
}

void ordenarGamesPreco() {
    Game *games = NULL;
    int qtd = 0;

    carregarGames(&games, &qtd);
    if (qtd == 0) {
        printf("Nenhum game cadastrado.\\n");
        return;
    }

    quicksortPreco(games, 0, qtd - 1);
    printf("Games ordenados por preco:\\n");
    for (int i = 0; i < qtd; i++) {
        printf("%d | %s | %s | %.2f | %s\\n",
               games[i].codigo, games[i].nome, games[i].genero,
               games[i].preco, games[i].promocao ? "Sim" : "Nao");
    }

    free(games);
}

int buscarGame(int codigo) {
    Game *games = NULL;
    int qtd = 0;

    carregarGames(&games, &qtd);

    if (qtd == 0) {
        free(games);
        return -1;
    }

    // Ordenar pelo código para busca binária
    quicksortPreco(games, 0, qtd - 1);

    int low = 0, high = qtd - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (games[mid].codigo == codigo) {
            printf("Game encontrado:\\n");
            printf("Codigo: %d\\nNome: %s\\nGenero: %s\\nPreco: %.2f\\nPromocao: %s\\n",
                   games[mid].codigo, games[mid].nome, games[mid].genero,
                   games[mid].preco, games[mid].promocao ? "Sim" : "Nao");
            free(games);
            return mid;
        } else if (games[mid].codigo < codigo) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    printf("Game nao encontrado.\\n");
    free(games);
    return -1;
}

void listarGamesPromocao() {
    Game *games = NULL;
    int qtd = 0;
    int achou = 0;

    carregarGames(&games, &qtd);

    printf("Games em promocao:\\n");
    for (int i = 0; i < qtd; i++) {
        if (games[i].promocao) {
            printf("%d | %s | %s | %.2f\\n",
                   games[i].codigo, games[i].nome, games[i].genero, games[i].preco);
            achou = 1;
        }
    }
    if (!achou) {
        printf("Nenhum game em promocao.\\n");
    }
    free(games);
}

void listarGamesGenero(const char *genero) {
    Game *games = NULL;
    int qtd = 0;
    int achou = 0;

    carregarGames(&games, &qtd);

    printf("Games do genero '%s':\\n", genero);
    for (int i = 0; i < qtd; i++) {
        if (strcmp(games[i].genero, genero) == 0) {
            printf("%d | %s | %.2f | Promocao: %s\\n",
                   games[i].codigo, games[i].nome,
                   games[i].preco, games[i].promocao ? "Sim" : "Nao");
            achou = 1;
        }
    }
    if (!achou) {
        printf("Nenhum game encontrado para esse genero.\\n");
    }
    free(games);
}
