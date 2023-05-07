#include <stdio.h>
#include "game.c"

int readInt(int lowerBound, int upperBound) {
    int number = lowerBound - 1;
    do {
        fscanf(stdin, "%d", &number);
        fflush(stdin);
        if(number < lowerBound || number > upperBound) {
            fprintf(stdout, "Please enter a number between %d and %d: ", lowerBound, upperBound);
        }
    } while (number < lowerBound || number > upperBound);
    return number;
}

int main() {
    fprintf(stdout, "Welcome to the tiC-taC-toe!\n\n");
    fprintf(stdout, "First of all, please sign up the players!\n");
    fprintf(stdout, "How many players want to play? ");
    int playerNumber = readInt(2, 10);
    fprintf(stdout, "Great! %s\n", 
        playerNumber == 2 ? "It looks like a traditional tic-tac-toe game!" : 
        playerNumber < 5 ? "You are really a group!" :
        "Now that's what I call a tiC-taC-toe BATTLE!"
    );
    fprintf(stdout, "\nNow signup the players!\n");
    Game *game = initGame(playerNumber);
    return 0;
}
