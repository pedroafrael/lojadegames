#ifndef GAME_H
#define GAME_H

#define MAX_NOME 100
#define MAX_GENERO 50

typedef struct {
    int codigo;
    char nome[MAX_NOME];
    char genero[MAX_GENERO];
    float preco;
    int promocao;
} Game;

void cadastrarGame();
void listarGames();
void editarGame();
void excluirGame();
int buscarGame(int codigo);
void listarGamesPromocao();
void listarGamesGenero(const char *genero);
void ordenarGamesPreco();
void carregarGames(Game **games, int *qtd);
void salvarGames(Game *games, int qtd);

#endif
