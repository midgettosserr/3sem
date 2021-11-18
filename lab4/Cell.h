#ifndef CELL_H
#define CELL_H

#include "Squad.h"

enum CellTypes {CellEmpty, CellWall, CellNothing, CellSummoner, CellSquad, CellEnd};

//класс клетка поля
class Cell {
private:
	CellTypes type;
	Squad *squad;
public:
	Cell(CellTypes type = CellEmpty, Squad *squad = nullptr);

	CellTypes getType() const {return type;}
	Squad *getsquad() const {return squad;}

	void setType(CellTypes type, Squad *squad = nullptr);
	void setSquad(Squad *squad);
};

#endif