#ifndef CONSOLE_GAME_H
#define CONSOLE_GAME_H

#include "Table.h"
#include "AmoralSquad.h"
#include "NormalSquad.h"
#include "AmoralResurrectedSquad.h"
#include "NormalResurrectedSquad.h"
#include "Level.h"
#include "Summoner.h"

#include <stdexcept>
#include <limits>

class ConsoleGame {
private:
    Level level;
    Table table;
    Summoner player1;
    Summoner player2;
    Summoner *currentPlayer;
    int x1, y1, x2, y2, x, y;

    //int x, int y;

    bool quit;

    void printMap() const;

    bool mainMenu();
    bool summonMenu();
    bool schoolMenu();

    AmoralSquad *findSquadToMove(int &x, int &y);
    bool findEmptyCell(int &x, int &y) const;

    bool readSkillsFromFile();
    bool readMapFromFile();
    bool saveGame(std::string filename);
    bool loadGame(std::string filename);

public:
    ConsoleGame();
    ~ConsoleGame();

    void startNewGame();

    void makeMove();
    bool gameEnded();
    void printWinner();

};

#endif