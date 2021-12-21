#ifndef LEVEL_H
#define LEVEL_H

#include "Cell.h"
#include "AmoralSquad.h"

#include <stdexcept>

class Level {
private:
    Cell **field;
    int rows, cols;
public:
    Level(int, int);
    ~Level();

    void setSize(int rows, int cols);
    int getRows() const {return rows;}
    int getCols() const {return cols;}

    CellTypes getCell(int x, int y) const;
    void setCell(CellTypes val, int x, int y);

    void setSquad(int x, int y, AmoralSquad *squad);
    AmoralSquad *getSquad(int x, int y) const;

    AmoralSquad *removeSquad(int x, int y);
};

#endif
