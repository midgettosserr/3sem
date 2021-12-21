#include "Level.h"

Level::Level(int rows, int cols): rows(rows), cols(cols) {
    if (rows < 1 || cols < 1) {
        throw std::invalid_argument("invalid size");
    }
    field = new Cell*[rows];
    for (int i = 0; i < rows; i++) {
        field[i] = new Cell[cols];
    }
}

Level::~Level() {
    for (int i = 0; i < rows; i++) {
        delete [] field[i];
    }
    delete [] field;
}

void Level::setSize(int rows, int cols) {
    if (rows < 1 || cols < 1) {
        throw std::invalid_argument("invalid size");
    }
    Cell **tmp = new Cell*[rows];
    for (int i = 0; i < rows; i++) {
        tmp[i] = new Cell[cols];
        if (i < this->rows) {
            for (int j = 0; j < cols && j < this->cols; j++) {
                tmp[i][j] = std::move(field[i][j]);
            }
        }
    }
    for (int i = 0; i < this->rows; i++) {
        delete [] field[i];
    }
    delete [] field;
    field = tmp;
    this->rows = rows;
    this->cols = cols;
}

void Level::setCell(CellTypes val, int x, int y) {
    if (x < 0 || y < 0 || x >= rows || y >= cols) {
        throw std::out_of_range("invalid coordinates");
    }
    field[x][y].setType(val);
}

CellTypes Level::getCell(int x, int y) const {
    if (x < 0 || y < 0 || x >= rows || y >= cols) {
        throw std::out_of_range("invalid coordinates");
    }
    return field[x][y].getType();
}

void Level::setSquad(int x, int y, AmoralSquad *squad) {
    if (x < 0 || y < 0 || x >= rows || y >= cols) {
        throw std::out_of_range("invalid coordinates");
    }
    field[x][y].setSquad(squad);
}

AmoralSquad *Level::getSquad(int x, int y) const {
    if (x < 0 || y < 0 || x >= rows || y >= cols) {
        throw std::out_of_range("invalid coordinates");
    }
    return field[x][y].getSquad();
}

AmoralSquad *Level::removeSquad(int x, int y) {
    if (x < 0 || y < 0 || x >= rows || y >= cols) {
        throw std::out_of_range("invalid coordinates");
    }
    return field[x][y].removeSquad();
}
