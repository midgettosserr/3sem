#include "ConsoleGame.h"
#include <iostream>

template<class T>
void input(T& data) {
    while (!(std::cin >> data)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "\nОшибка, повторите ввод: ";
    }
    std::cin.ignore();
}

template<>
void input(std::string& data) {
    getline(std::cin, data);
}

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
    std::cout << "g - сделать передвижение в указанную точку" << std::endl;
    std::cout << "a - атаковать указанную точку" << std::endl;
    std::cout << "h - восстановить свой отряд" << std::endl;
    std::cout << "r - аккумулировать энергию" << std::endl;
    std::cout << "c - меню призыва" << std::endl;
    std::cout << "o - меню улучшения школы" << std::endl;
    //std::cout << "f - выстрелить указанную точку" << std::endl;
    //std::cout << "s - выйти и сохранить игру в файл" << std::endl;
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
            std::cout << "Инициатива отряда меньше инициативы призывателя: выберите r, c или o" << std::endl;
            return false;
        }
    }
    if (squad && (option == 'r' || option == 'c' || option == 'o') &&
        squad->getInitiative() > currentPlayer->getInitiative()) {
        std::cout << "Инициатива отряда больше инициативы призывателя: выберите g, a или h" << std::endl;
        return false;
    }
    switch (option) {
        case 'g':
            std::cout << "Текущие координаты отряда: " << i << " " << j << std::endl;
            std::cout << "Введите координаты точки, в которую необходимо переместить отряд: ";
            input(i1);
            input(j1);
            if (squad->getSpeed() < abs(i-i1) + abs(j-j1)) {
                std::cout << "Недостаточная скорость! Отряд не перемещен" << std::endl;
                return false;
            }
            try {
                level.setSquad(i1, j1, squad);
            }
            catch (const std::exception& ex) {
                std::cout << "Не удалось переместить отряд: "  << ex.what() << std::endl;
                return false;
            }
            level.setCell(CellEmpty, i, j);
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
            if (squad->getSpeed() < abs(i-i1) + abs(j-j1)) {
                std::cout << "Недостаточная скорость!" << std::endl;
                return false;
            }
            if (level.getCell(i1, j1) != CellSquad || level.getSquad(i1, j1)->getSummoner() == currentPlayer) {
                std::cout << "В указанной точке нет вражеского отряда!" << std::endl;
                return false;
            }
            std::cout << "Численность атакованого отряда до атаки: " << level.getSquad(i1, j1)->getCount() << std::endl;
            level.getSquad(i1, j1)->makeDamageTo(squad->getDamageFrom());
            if (NormalSquad *s = dynamic_cast<NormalSquad*>(squad)) {
                s->increaseMoral(5);
            }
            std::cout << "Численность атакованого отряда после атаки: " << level.getSquad(i1, j1)->getCount() << std::endl;
            squad->decreaseInitiative();
            return true;
        case 'h':
            if (AmoralResurrectedSquad *s = dynamic_cast<AmoralResurrectedSquad*>(squad)) {
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
            std::cout << "Энергия призывателя была: " << currentPlayer->getCurrentEnergy() << std::endl;
            currentPlayer->accumulateEnergy();
            currentPlayer->decreaseInitiative();
            std::cout << "Энергия призывателя стала: " << currentPlayer->getCurrentEnergy() << std::endl;
            return true;
        case 'c':
            return summonMenu();
        case 'o':
            return schoolMenu();
        default:
            std::cout << "Неверный пункт меню, повторите выбор" << std::endl;
            return false;
    }
}

bool ConsoleGame::summonMenu() {
    std::cout << "Меню призыва" << std::endl;
    std::cout << "Список школ:" << std::endl;
    for (Table::iterator it = table.begin(); it != table.end(); it++) {
        std::cout << it->getName() << std::endl;
        for (School::iterator it2 = it->begin(); it2 != it->end() ; it2++) {
            std::cout << "\t" << it2->getName() << " - " << it2->getCreature() << std::endl;
            std::cout << "\tМинимальное знание школы: " << it2->getMinKnowledge() << std::endl;
        }
    }
    std::string schoolname, skillname;
    std::cout << "Введите школу: ";
    input(schoolname);
    std::cout << "Введите умение: ";
    input(skillname);
    try {
        Skill *skill = table.getSkill(schoolname, skillname);
        int knowledge;
        try {
            knowledge = currentPlayer->getSchoolKnowledge(schoolname);
        }
        catch (const std::out_of_range&) {
            knowledge = 0;
        }
        if (skill->getMinKnowledge() <= knowledge) {
            int x, y;
            if (findEmptyCell(x, y)) {
                AmoralSquad *sq = new AmoralSquad(skill->getCreature(), schoolname);
                sq->setSummoner(currentPlayer);
                level.setSquad(x, y, sq);
                currentPlayer->decreaseInitiative();
            }
            else {
                std::cout << "Нет свободных клеток для отряда" << std::endl;
            }
        }
        else {
            std::cout << "Знание школы (" << knowledge << ") недостаточно для призыва" << std::endl;
            return false;
        }
    }
    catch (const std::out_of_range& ex) {
        std::cout << "Некорректная школа или умение: " << ex.what() << std::endl;
        return false;
    }
    return true;
}

bool ConsoleGame::schoolMenu() {
    std::cout << "Меню улучшения школы" << std::endl;
    std::cout << "Список школ:" << std::endl;
    for (Table::iterator it = table.begin(); it != table.end(); it++) {
        std::cout << it->getName() << std::endl;
    }
    std::string schoolname;
    std::cout << "Введите школу для улучшения: ";
    input(schoolname);
    std::cout << "Текущий опыт " << currentPlayer->getExperience() << std::endl;
    std::cout << "Потратить на улучшение: ";
    int exp;
    input(exp);
    try {
        currentPlayer->improveSchool(schoolname, exp);
        currentPlayer->decreaseInitiative();
    }
    catch (const std::out_of_range& ex) {
        std::cout << "Ошибка ввода опыта" << std::endl;
        return false;
    }
    return true;
}

AmoralSquad* ConsoleGame::findSquadToMove(int &x, int &y) const {
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
    return squad;
}

bool ConsoleGame::findEmptyCell(int &x, int &y) const {
    for (int i = 0; i < level.getCols(); i++) {
        for (int j = 0; j < level.getRows(); j++) {
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

ConsoleGame::ConsoleGame() : level(20, 20), player1("Первый призыватель", 100, 100, 100, 100, 100, 0.5, 100), player2("Второй призыватель", 100, 100, 100, 100, 100, 0.5, 100) {
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
    std::cout << winner->getName() << std::endl;
}
