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

	void setSize(int rows, int cols);
	int getRows() const;
	int getCols() const;

	void getCell(int x, int y) const;
	void setCell(int val, int x, int y);

	void setSquad(int x, int y, Squad *squad);
};

#endif