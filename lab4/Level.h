#ifndef LEVEL_H
#define LEVEL_H

#include "Cell.h"
#include "Squad.h"

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

	void getCell(int x, int y) const;
	void setCell(CellTypes val, int x, int y);

	void setSquad(int x, int y, Squad *squad);
};

#endif