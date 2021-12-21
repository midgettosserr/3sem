#ifndef CELL_H
#define CELL_H

#include "AmoralSquad.h"
#include <stdexcept>

enum CellTypes {CellEmpty, CellWall, CellNothing, CellSummoner, CellSquad, CellEnd};

//класс клетка поля
class Cell {
private:
    CellTypes type;
    AmoralSquad *squad;
public:
    Cell(CellTypes type = CellEmpty, AmoralSquad *squad = nullptr);
    Cell(const Cell&) = delete;
    Cell(Cell&&);
    Cell &operator=(const Cell&) = delete;
    Cell &operator=(Cell&&);
    ~Cell() {delete squad;}
    
    CellTypes getType() const {return type;}
    AmoralSquad *getSquad() const {return squad;}

    void setType(CellTypes type, AmoralSquad *squad = nullptr);
    void setSquad(AmoralSquad *squad);

    AmoralSquad *removeSquad();
};

#endif
