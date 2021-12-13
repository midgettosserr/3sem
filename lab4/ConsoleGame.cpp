#include "ConsoleGame.h"
#include <vector>
#include <iostream>
//#include <fstream>
//#include <sstream>

template<class T>
void input(T &data) {
    while (!(std::cin >> data)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nОшибка, повторите ввод: ";
    }
    std::cin.ignore();
}

template<>
void input(std::string &data) {
    getline(std::cin, data);
}

//bool quit;

void ConsoleGame::printMap() const {
    char userSquad = 'a';
    char enemySquad = 'A';
    for (int i = 0; i < level.getCols(); i++) {
        for (int j = 0; j < level.getRows(); j++) {
            switch (level.getCell(i, j)) {
                case CellEmpty:
                    std::cout << '.';
                    break;
                case CellWall:
                    std::cout << '#';
                    break;
                case CellNothing:
                    std::cout << ' ';
                    break;
                case CellSummoner:
                    if (i == x && j == y) {
                        std::cout << '@';
                    }
                    else {
                        std::cout << '*';
                    }
                    break;
                case CellSquad:
                    if (level.getSquad(i, j)->getSummoner() == currentPlayer) {
                        std::cout << userSquad++;
                    }
                    else {
                        std::cout << enemySquad++;
                    }
                    break;
                case CellEnd:
                    std::cout << "";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

bool ConsoleGame::mainMenu() {
    int i, j, i1, j1;
    AmoralSquad *squad = findSquadToMove(i, j);
    std::cout << "Следующий ход:" << std::endl;
    std::cout << currentPlayer->getName() << std::endl;
    printMap();
    std::cout << "g - сделать передвижение в указанную точку" << std::endl;
    std::cout << "a - атаковать указанную точкуу" << std::endl;
    std::cout << "h - восстановить свой отряд" << std::endl;
    std::cout << "r - аккумулировать энергию" << std::endl;
    std::cout << "c - меню призыва" << std::endl;
    std::cout << "o - меню улучшения школы" << std::endl;
    //std::cout << "f - выстрелить указанную точку" << std::endl;
    std::cout << "s - выйти и сохранить игру в файл" << std::endl;
    char option;
    input(option);
    int i, j, i1, j1;
    AmoralSquad *squad = findSquadToMove(i, j);
    if ((option == 'g' || option == 'a' || option == 'h')) {
        if (!squad) {
            std::cout << "Нет ни одного отряда" << std::endl;
            return false;
        }
        else if (squad->getInitiative() < currentPlayer->getInitiative()) {
            std::cout << "Инициатива отряда меньше инициативы призывателя: выберите r, c или о" << std::endl;
            return false;
        }
    }
    if (squad && (option == 'r' || option == 'c' || option == 'o') && squad->getInitiative() > currentPlayer->getInitiative()) {
        std::cout << "Инициатива отряда больше иницативы призывателя: выберите g, a или h" << std::endl;
        return false;
    }
    switch (option) {
        case 'g':
            std::cout << "Текущие координаты отряда: " << i << " " << j << std::endl;
            std::cout << "Введите координаты точки, в которую необходимо переместить отряд: ";
            input(i1);
            input(j1);
            if (squad->getSpeed() < abs(i - i1) + abs(j - j1)) {
                std::cout << "Недостаточная скорость! Отряд не перемещен" << std::endl;
                return false;
            }
            try {
                level.setSquad(i1, j1, level.removeSquad(i, j));
            }
            catch (const std::exception &ex) {
                std::cout << "Не удалось переместить отряд: " << ex.what() << std::endl;
                level.setSquad(i, j, squad);
                return false;
            }
            squad->decreaseInitiative();
            std::cout << "Отряд успешно перемещен" << std::endl;
            return true;
        case 'a':
            std::cout << "Текущие координаты отряда: " << i << " " << j << std::endl;
            std::cout << "Введите координаты атакуемой точки: ";
            input(i1);
            input(j1);
            if (i1 < 0 || j1 < 0 || i1 >= level.getRows() || j1 >= level.getCols()) {
                std::cout << "Некорректные координаты!" << std::endl;
                return false;
            }
            if (squad->getSpeed() < abs(i-i1) + abs(j-j1)){
                std::cout << "Недостаточная скорость!" << std::endl;
                return false;
            }
            if (level.getCell(i1, j1) != CellSquad || level.getSquad(i1, j1)->getSummoner() == currentPlayer) {
                std::cout << "В указанной точке нет вражеского отряда!" << std::endl;
                return false;
            }
            std::cout << "Численность атакованного отряда до атаки: " << level.getSquad(i1, j1)->getCount() <<std::endl;
            level.getSquad(i1, j1) ->makeDamageTo(squad->getDamageFrom());
            if (NormalSquad *s = dynamic_cast<NormalSquad*>(squad)) {
                s->increaseMoral;
            }
            std::cout << "Численность атакованного отряда после атаки: " << level.getSquad(i1, j1)->getCount() << std::endl;
            squad->decreaseInitiative();
            return true;
        case 'h':
            if (AmoralResurrectedSquad *s = dynamic_cast<AmoralResurrectedSquad>(squad)) {
                std::cout << "Численность отряда до попытки воскрешения: " << s->getCount() << std::endl;
                s->resurrect();
                s->decreaseInitiative();
                std::cout << "Численность отряда после попытки воскрешения: " << s->getCount() << std::endl;
                return true;
            }
            else {
                std::cout << "Отряд не является воскрешаемым" << std::endl;
                return false;
            }
        case 'r':
            std::cout << "Энергия призываетля была: " << currentPlayer->getCurrentEnergy() << std::endl;
            currentPlayer->accumulateEnergy();
            currentPlayer->decreaseInitiative();
            std::cout << "Энергия призывателя стала: " << currentPlayer->getCurrentEnergy() << std::endl;
            return true;
        case 'c':
            return summonMenu();
        case 'o':
            return schoolMenu();
        //case 's':
            //return false;
        default:
            std::cout << "Неверный пункт меню, повторите выбор" << std::endl;
            return false;
    }
}

bool summonMenu();
bool schoolMenu();

AmoralSquad *ConsoleGame::findSquadToMove(int &x, int &y) {
    AmoralSquad *squad = nullptr;
    for (int i = 0; i < level.getCols(); i++) {
        for (int j = 0; j < level.getRows(); j++) {
            if (level.getCell(i, j) == CellSquad) {
                if (squad == nullptr || level.getSquad(i, j)->getInitiative() > squad->getInitiative()) {
                    squad = level.getSquad(i, j);
                    x = i;
                    y = j;
                }
            }
        }
    }
    if (squad && squad->getInitiative() > currentPlayer->getInitiative()) {
        currentPlayer = squad->getSummoner();
        this->x = currentPlayer == &player1 ? x1 : x2;
        this->y = currentPlayer == &player2 ? y1 : y2;
    }
    return squad;
}

bool ConsoleGame::findEmptyCell(int &x, int &y) const {
    for (int i = 0; i < level.getCols(); i++) {
        for (int j = 0; j < getRows(); j++) {
            if (level.getCell(i, j) == CellEmpty) {
                x = i;
                y = j;
                return true;
            }
        }
    }
    return false;
}

/*bool readSkillsFromFile();
bool readMapFromFile();

bool saveGame(std::string filename);
bool loadGame(std::string filename);*/


ConsoleGame::ConsoleGame() : level(10, 10), player1("Первый призыватель", 100, 100, 100, 100, 100, 0.5, 100), player2("Второй призыватель", 100, 100, 100, 100, 100, 0.5, 100) {
    currentPlayer = &player1;
    level.setCell(CellSummoner, 0, 0);
    x = 0;
    y = 0;
    level.setCell(CellSummoner, 9, 9);
    table.addSchool("робототехника");
    table.addSkill("робототехника", Skill("ИИ", "робот", 10, 10, 0.8));
    table.addSchool("биотехнологии");
    table.addSkill("биотехнологии", Skill("поедание плоти", "зомби", 20, 15, 0.7));
}

ConsoleGame::~ConsoleGame() {

}

void ConsoleGame::startNewGame() {
    
}


void ConsoleGame::makeMove() {
    printMap();
    if (mainMenu()) {
        currentPlayer = player1.getInitiative() > player2.getInitiative() ? &player1 : &player2;
        if (currentPlayer == &player1) {
            x = 0;
            y = 0;
        }
        else {
            x = 9;
            y = 9;
        }
        std::cout << "Следующий ход:" << std::endl;
        std::cout << currentPlayer->getName() << std::endl;
    }
    else {
        std::cout << "Ход не совершен, повтор хода" << std::endl;
    }
}

bool ConsoleGame::gameEnded() {
    return player1.getCurrentHealth() <= 0 || player2.getCurrentHealth() <= 0;
}

void ConsoleGame::printWinner() {
    Summoner *winner = player1.getCurrentHealth() > player2.getCurrentHealth() ? &player1 : &player2;
    std::cout << "Игра окончена! Победитель: " << winner->getName() << std::endl;
}