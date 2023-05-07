#include <stdlib.h>
#include "players.c"

typedef struct {
    Player *players;
    int playerNumber;
    int currentPlayer;
} Game;

Game *initGame(int playerNumber) {
    Game *game = (Game*) malloc(sizeof (Game));
    game->playerNumber = playerNumber;
    game->players = (Player*) malloc(sizeof (Player) * playerNumber);
    for (int i = 0; i < playerNumber; ++i) {
        game->players[i] = signupPlayer();
    }
    game->currentPlayer = 0;
    return game;
}

void freeGame(Game *game) {
    for (int i = 0; i < game->playerNumber; ++i) {
        freePlayer(game->players[i]);
    }
    free(game->players);
    free(game);
}
