#include "ConsoleGame.h"
#include <iostream>

int main() {
    ConsoleGame game;
    game.startNewGame();
    while (!game.gameEnded()) {
        game.makeMove();
    }
    game.printWinner();
    return 0;
}