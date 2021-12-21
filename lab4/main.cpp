#include "ConsoleGame.h"
#include <iostream>

int main() {
    std::cout << "Загрузить игру из файла? да/нет" << std::endl;
    std::string ans, filename = "", first = "", second = "";
    std::getline(std::cin, ans);
    bool fromFile = ans == "да" || ans == "д" || ans == "yes" || ans == "y";
    if (fromFile) {
        std::cout << "Введите имя файла: ";
        std::getline(std::cin, filename);
    }
    else {
        std::cout << "Введите имя первого игрока: ";
        std::getline(std::cin, first);
        std::cout << "Введите имя второго игрока: ";
        std::getline(std::cin, second);
    }
    ConsoleGame game(first, second, fromFile, filename);
    while (!game.gameEnded()) {
        game.makeMove();
    }
    game.printWinner();
    return 0;
}
