#ifndef CELL_H
#define CELL_H

#include "AmoralSquad.h"

enum CellTypes {CellEmpty, CellWall, CellNothing, CellSummoner, CellSquad, CellEnd};

//класс клетка поля
class Cell {
private:
	CellTypes type;
	AmoralSquad *squad;
public:
	Cell(CellTypes type = CellEmpty, AmoralSquad *squad = nullptr);

	CellTypes getType() const {return type;}
	AmoralSquad *getsquad() const {return squad;}

	void setType(CellTypes type, AmoralSquad *squad = nullptr);
	void setSquad(AmoralSquad *squad);
};

#endif