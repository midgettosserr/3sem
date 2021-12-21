#include "ConsoleGame.h"
#include "Vector.h"
#include <iostream>
#include <fstream>
#include <sstream>

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

bool ConsoleGame::readSkillsFromFile() {
    std::ifstream file("skills.txt");
    if (!file.is_open()) {
        return false;
    }
    std::string str;
    std::string currentSchool = "";
    while (std::getline(file, str)) {
        if (str.find(',') == std::string::npos) {
            table.addSchool(str);
            currentSchool = str;
        }
        else {
            if (currentSchool.empty()) {
                return false;
            }
            std::stringstream s(str);
            std::string tmp;
            mycontainers::vector<std::string> vec;
            while (std::getline(s, tmp, ',')) {
                auto start_it = tmp.begin();
                auto end_it = tmp.rbegin();
                while (std::isspace(*start_it))
                    ++start_it;
                while (std::isspace(*end_it))
                    ++end_it;
                vec.push_back(std::string(start_it, end_it.base()));
            }
            if (vec.size() != 10) {
                file.close();
                return false;
            }
            try {
                bool normal = std::stoi(vec[8]) == 1;
                bool resurrcted = std::stoi(vec[9]) == 1;
                Skill::SquadType type = Skill::AmoralType;
                if (normal && !resurrcted) {
                    type = Skill::NormalType;
                }
                else if (normal && resurrcted) {
                    type = Skill::NormalResurrectedType;
                }
                else if (!normal && resurrcted) {
                    type = Skill::AmoralResurrectedType;
                }
                Skill::Creature creatue {vec[1], std::stoi(vec[5]), std::stoi(vec[6]), std::stoi(vec[7])};
                table.addSkill(currentSchool, Skill(vec[0], creatue, std::stoi(vec[2]), std::stoi(vec[3]), std::stod(vec[4])));
            }
            catch (const std::exception&) {
                file.close();
                return false;
            }
        }
    }
    file.close();
    return true;
}

bool ConsoleGame::readMapFromFile() {
    std::ifstream file("map.txt");
    if (!file.is_open()) {
        return false;
    }
    int rows = 0;
    int cols = 0;
    std::string str;
    while (std::getline(file, str)) {
        if (str.empty()) {
            return false;
        }
        if (rows == 0) {
            cols = (int)str.size();
        }
        else if (cols != str.size()) {
            file.close();
            return false;
        }
        rows++;
        level.setSize(rows, cols);
        for (int i = 0; i < str.size(); i++) {
            switch (str[i]) {
                case '.':
                    level.setCell(CellEmpty, rows-1, i);
                    break;
                case ' ':
                    level.setCell(CellNothing, rows-1, i);
                    break;
                case '#':
                    level.setCell(CellWall, rows-1, i);
                    break;
                case '@':
                    level.setCell(CellSummoner, rows-1, i);
                    x1 = x = rows-1;
                    y1 = y = i;
                    break;
                case '*':
                    level.setCell(CellSummoner, rows-1, i);
                    x2 = rows-1;
                    y2 = i;
                    break;
                default:
                    return false;
            }
        }
    }
    return rows > 0;
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
    int i, j, i1, j1;
    AmoralSquad *squad = findSquadToMove(i, j);
    std::cout << "Следующий ход:" << std::endl;
    std::cout << currentPlayer->getName() << std::endl;
    printMap();
    std::cout << "g - сделать передвижение в указанную точку" << std::endl;
    std::cout << "a - атаковать указанную точку" << std::endl;
    std::cout << "h - восстановить свой отряд" << std::endl;
    std::cout << "r - аккумулировать энергию" << std::endl;
    std::cout << "c - меню призыва" << std::endl;
    std::cout << "o - меню улучшения школы" << std::endl;
    std::cout << "s - выйти и сохранить игру в файл" << std::endl;
    char option;
    input(option);
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
                level.setSquad(i1, j1, level.removeSquad(i, j));
            }
            catch (const std::exception &ex) {
                std::cout << "Не удалось переместить отряд: "  << ex.what() << std::endl;
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
            if (squad->getSpeed() < abs(i-i1) + abs(j-j1)) {
                std::cout << "Недостаточная скорость!" << std::endl;
                return false;
            }
            if (level.getCell(i1, j1) == CellSummoner) {
                if (x == i1 && y == j1) {
                    std::cout << "Отряд не может атаковать собственного призывателя" << std::endl;
                    return false;
                }
                else {
                    Summoner *enemy = currentPlayer == &player1 ? &player2 : &player1;
                    std::cout << "Текущее здоровье вражеского призывателя: " << enemy->getCurrentHealth() << std::endl;
                    enemy->makeDamage(squad->getDamageFrom());
                    std::cout << "Здоровье вражеского призывателя после атаки: " << enemy->getCurrentHealth() << std::endl;
                    if (NormalSquad *s = dynamic_cast<NormalSquad*>(squad)) {
                        s->increaseMoral(5);
                    }
                    squad->decreaseInitiative();
                }
            }
            else {
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
                if (level.getSquad(i1, j1)->getCount() == 0) {
                    std::cout << "Отряд уничтожен!" << std::endl;
                    currentPlayer->gainExperience(level.getSquad(i1, j1)->getExperience());
                    level.setCell(CellEmpty, i1, j1);
                }
                squad->decreaseInitiative();
            }
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
        case 's': {
            std::cout << "Введите имя файла: ";
            std::string filename;
            std::cin >> filename;
            if (saveGame(filename)) {
                std::cout << "Игра сохранена в файл " << filename << std::endl;
            }
            else {
                std::cout << "Не удалось сохранить игру" << std::endl;
            }
            quit = true;
            return false;
        }
        default:
            std::cout << "Неверный пункт меню, повторите выбор" << std::endl;
            return false;
    }
}

bool ConsoleGame::summonMenu() {
    std::cout << "Меню призыва" << std::endl;
    std::cout << "Список школ:" << std::endl;
    for (auto it = table.begin(); it != table.end(); it++) {
        std::cout << it->getName() << std::endl;
        for (auto it2 = it->begin(); it2 != it->end() ; it2++) {
            std::cout << "\t" << it2->getName() << " - " << it2->getCreature().name << std::endl;
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
        int energy = currentPlayer->getCurrentEnergy();
        if (skill->getMinKnowledge() <= knowledge && skill->getEnergy() <= energy) {
            int x, y;
            if (findEmptyCell(x, y)) {
                AmoralSquad *sq;
                switch (skill->getCreature().type) {
                    case Skill::AmoralType:
                        sq = new AmoralSquad(skill->getCreature().name, schoolname);
                        break;
                    case Skill::NormalType:
                        sq = new NormalSquad(skill->getCreature().name, schoolname);
                        break;
                    case Skill::AmoralResurrectedType:
                        sq = new AmoralResurrectedSquad(skill->getCreature().name, schoolname);
                        break;
                    case Skill::NormalResurrectedType:
                        sq = new NormalResurrectedSquad(skill->getCreature().name, schoolname);
                        break;
                }
                sq->setInitiative(100);
                sq->setSpeed(skill->getCreature().speed);
                sq->setDamage(skill->getCreature().damage);
                sq->setProtection(100);
                sq->setCount(skill->getKoefficient() * knowledge);
                sq->setExperience(skill->getCreature().experience);
                sq->setSummoner(currentPlayer);
                level.setSquad(x, y, sq);
                currentPlayer->decreaseInitiative();
                currentPlayer->setCurrentEnergy(energy - skill->getEnergy());
            }
            else {
                std::cout << "Нет свободных клеток для отряда" << std::endl;
            }
        }
        else {
            std::cout << "Невозможно призвать отряд:" << std::endl;
            std::cout << "Знание школы - " << knowledge << ", для призыва нужно - " << skill->getMinKnowledge() << std::endl;
            std::cout << "Энергия - " << energy << ", для призыва нужно - " << skill->getEnergy() << std::endl;
            return false;
        }
    }
    catch (const std::out_of_range &ex) {
        std::cout << "Некорректная школа или умение: " << ex.what() << std::endl;
        return false;
    }
    return true;
}

bool ConsoleGame::schoolMenu() {
    std::cout << "Меню улучшения школы" << std::endl;
    std::cout << "Список школ:" << std::endl;
    for (auto it = table.begin(); it != table.end(); it++) {
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
    catch (const std::out_of_range &ex) {
        std::cout << "Ошибка ввода опыта" << std::endl;
        return false;
    }
    return true;
}

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
        this->y = currentPlayer == &player1 ? y1 : y2;
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

ConsoleGame::ConsoleGame(std::string firstName, std::string secondName, bool loadFromFile, std::string filename) : level(1, 1), player1(firstName, 100, 100, 100, 100, 100, 0.5, 100), player2(secondName, 100, 100, 100, 100, 100, 0.5, 100), quit(false) {
    if (!readSkillsFromFile()) {
        std::cout << "Ошибка загрузки файла skills.txt" << std::endl;
        quit = true;
        return;
    }
    if (loadFromFile) {
        if (!loadGame(filename)) {
            std::cout << "Не удалось загрузить игру из файла" << std::endl;
            quit = true;
        }
    }
    else {
        if (!readMapFromFile()) {
            std::cout << "Ошибка загрузки файла map.txt" << std::endl;
            quit = true;
            return;
        }
        currentPlayer = &player1;
    }
    printMap();

    /*currentPlayer = &player1;
    level.setCell(CellSummoner, 0, 0);
    x = 0;
    y = 0;
    level.setCell(CellSummoner, 9, 9);
    table.addSchool("робототехника");
    table.addSkill("робототехника", Skill("ИИ", "робот", 10, 10, 0.8));
    table.addSchool("биотехнологии");
    table.addSkill("биотехнологии", Skill("поедание плоти", "зомби", 20, 15, 0.7));*/
}

ConsoleGame::~ConsoleGame() {
    
}

/*void ConsoleGame::startNewGame() {
    
}*/

void ConsoleGame::makeMove() {
    if (mainMenu()) {
        currentPlayer = player1.getInitiative() > player2.getInitiative() ? &player1 : &player2;
        x = currentPlayer == &player1 ? x1 : x2;
        y = currentPlayer == &player1 ? y1 : y2;
    }
    else {
        std::cout << "Ход не совершен, повтор хода" << std::endl;
    }
    /*else {
        x = 9;
        y = 9;
    }
    std::cout << "Следующий ход:" << std::endl;
    std::cout << currentPlayer->getName() << std::endl;
    else {
        std::cout << "Ход не совершен, повтор хода" << std::endl;*/
}

bool ConsoleGame::gameEnded() {
    return player1.getCurrentHealth() <= 0 || player2.getCurrentHealth() <= 0 || quit;
}

void ConsoleGame::printWinner() {
    Summoner *winner = player1.getCurrentHealth() > player2.getCurrentHealth() ? &player1 : &player2;
    std::cout << "Игра окончена! Победитель: " << winner->getName() << std::endl;
}

bool ConsoleGame::saveGame(std::string filename) {
    std::ofstream file(filename);
    if (!file.is_open())
        return false;
    file << level.getRows() << " " << level.getCols() << " ";
    for (int i = 0; i < level.getCols(); i++) {
        for (int j = 0; j < level.getRows(); j++) {
            file << level.getCell(i, j) << " ";
            if (level.getCell(i, j) == CellSquad) {
                AmoralSquad *s = level.getSquad(i, j);
                if (s->getSummoner() == &player1) {
                    file << "1 ";
                }
                else {
                    file << "2 ";
                }
                file << s->type() << " ";
                if (NormalSquad *ns = dynamic_cast<NormalSquad*>(s)) {
                    file << ns->removeMoral() << " ";
                }
                file << s->getInitiative() << " " << s->getSpeed() << " " << s->getDamage() << " " << s->getProtection() << " " << s->getCount() << " " << s->getExperience() << " " << s->getCreatureName() << "," << s->getSchool() << ",";
            }
        }
    }
    file << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x << " " << y << " ";
    file << player1.getName() << "," << player1.getInitiative() << " " << player1.getMaxHealth() << " " << player1.getCurrentHealth() << " " << player1.getMaxEnergy() << " " << player1.getCurrentEnergy() << " " << player1.getAccumKoef() << " " << player1.getExperience() << " " << player1.size();
    for (auto it = player1.begin(); it != player1.end(); it++) {
        file << it->first << "," << it->second << " ";
    }
    file << player2.getName() << "," << player2.getInitiative() << " " << player2.getMaxHealth() << " " << player2.getCurrentHealth() << " " << player2.getMaxEnergy() << " " << player2.getCurrentEnergy() << " " << player2.getAccumKoef() << " " << player2.getExperience() << " " << player2.size();
    for (auto it = player2.begin(); it != player2.end(); it++) {
        file << it->first << "," << it->second << " ";
    }
    if (currentPlayer == &player1) {
        file << "1 ";
    }
    else {
        file << "2 ";
    }
    file.close();
    return true;
}

bool ConsoleGame::loadGame(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        return false;
    int rows, cols;
    file >> rows >> cols;
    if (file.fail()) return false;
    level.setSize(rows, cols);
    for (int i = 0; i < level.getCols(); i++) {
        for (int j = 0; j < level.getRows(); j++) {
            int t;
            file >> t;
            if ((CellTypes)t == CellSquad) {
                int pl, sqtype, moral = 0;
                file >> pl >> sqtype;
                if ((Skill::SquadType)sqtype == Skill::NormalType) {
                    file >> moral;
                }
                AmoralSquad *sq;
                switch ((Skill::SquadType)sqtype) {
                    case Skill::AmoralType:
                        sq = new AmoralSquad();
                        break;
                    case Skill::NormalType:
                        sq = new NormalSquad();
                        dynamic_cast<NormalSquad*>(sq)->increaseMoral(moral);
                        break;
                    case Skill::AmoralResurrectedType:
                        sq = new AmoralResurrectedSquad();
                        break;
                    case Skill::NormalResurrectedType:
                        sq = new NormalResurrectedSquad();
                        break;
                }
                int tmp;
                sq->setSummoner(pl == 1 ? &player1 : &player2);
                file >> tmp;
                sq->setInitiative(tmp);
                file >> tmp;
                sq->setSpeed(tmp);
                file >> tmp;
                sq->setDamage(tmp);
                file >> tmp;
                sq->setProtection(tmp);
                file >> tmp;
                sq->setCount(tmp);
                file >> tmp;
                sq->setExperience(tmp);
                std::string str;
                file.ignore();
                std::getline(file, str, ',');
                sq->setCreatureName(str);
                std::getline(file, str, ',');
                sq->setSchool(str);
                level.setSquad(i, j, sq);
            }
            else {
                level.setCell((CellTypes)t, i, j);
            }
        }
    }
    file >> x1 >> y1 >> x2 >> y2 >> x >> y;
    std::string str;
    file.ignore();
    std::getline(file, str, ',');
    player1.setName(str);
    int tmp, size;
    double k;
    file >> tmp;
    player1.setInitiative(tmp);
    file >> tmp;
    player1.setMaxHealth(tmp);
    file >> tmp;
    player1.setCurrentHealth(tmp);
    file >> tmp;
    player1.setMaxEnergy(tmp);
    file >> tmp;
    player1.setCurrentEnergy(tmp);
    file >> k;
    player1.setAccumKoef(k);
    file >> tmp;
    player1.setExperience(tmp);
    file >> size;
    for (int i = 0; i < size; i++) {
        file.ignore();
        std::getline(file, str, ',');
        file >> tmp;
        player1.setSchoolKnowledge(str, tmp);
    }
    file.ignore();
    std::getline(file, str, ',');
    player2.setName(str);
    file >> tmp;
    player2.setInitiative(tmp);
    file >> tmp;
    player2.setMaxHealth(tmp);
    file >> tmp;
    player2.setCurrentHealth(tmp);
    file >> tmp;
    player2.setMaxEnergy(tmp);
    file >> tmp;
    player2.setCurrentEnergy(tmp);
    file >> k;
    player2.setAccumKoef(k);
    file >> tmp;
    player2.setExperience(tmp);
    file >> size;
    for (int i = 0; i < size; i++) {
        file.ignore();
        std::getline(file, str, ',');
        file >> tmp;
        player1.setSchoolKnowledge(str, tmp);
    }
    file >> tmp;
    currentPlayer = tmp == 1 ? &player1 : &player2;
    bool result = !file.fail();
    file.close();
    return result;
}
