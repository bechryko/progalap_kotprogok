#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *name;
    char character;
    int score;
} Player;

Player signupPlayer() {
    static int playerNumber = 1;
    static char excludedCharacters[16];
    static int excludedCharactersLength = -1;
    if (playerNumber == 1) {
        char *copy = ".,\n\t ";
        while(copy[++excludedCharactersLength]);
        for (int i = 0; copy[i]; ++i) {
            excludedCharacters[i] = copy[i];
        }
    }
    fprintf(stdout, "Player %d\n", playerNumber++);
    Player player;
    player.name = (char*) malloc(sizeof (char) * 21);
    fprintf(stdout, "Name (max. 20 characters): ");
    fscanf(stdin, "%20s", player.name);
    fflush(stdin);
    fprintf(stdout, "Character: ");
    fscanf(stdin, "%c", &player.character);
    //TODO: check if character is in excludedCharacters
    fflush(stdin);
    player.score = 0;
    excludedCharacters[++excludedCharactersLength] = player.character;
    return player;
}

void freePlayer(Player player) {
    free(player.name);
}
