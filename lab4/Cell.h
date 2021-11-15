#ifndef CELL_H
#define CELL_H

#include "Squad.h"

//класс клетка поля
class Cell {
private:
	int type;
	Squad *squad;
public:
	Cell();
	Cell(int type, Squad *squad = nullptr);

	int getType() const;
	Squad *getsquad() const;

	void setType(int type);
	void setSquad(Squad *squad);
};

#endif