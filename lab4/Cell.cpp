#include "Cell.h"

Cell::Cell(CellTypes type, AmoralSquad *squad) : type(type), squad(squad) {
    if ((type != CellSquad && squad != nullptr) || (type == CellSquad && squad == nullptr)) {
        throw std::invalid_argument("squad can be only on squad-type cell");
    }
}

void Cell::setSquad(AmoralSquad *squad) {
    if (type != CellEmpty) {
        throw std::logic_error("the cell is not empty");
    }
    if (squad == nullptr) {
        throw std::invalid_argument("squad can't be null");
    }
    type = CellSquad;
    this->squad = squad;
}

void Cell::setType(CellTypes type, AmoralSquad *squad) {
    if (type == CellSquad) {
        setSquad(squad);
    }
    else {
        squad = nullptr;
    }
    this->type = type;
}

Cell::Cell(Cell &&cell) : type(cell.type) {
    squad = cell.squad;
    cell.squad = nullptr;
    cell.type = CellEmpty;
}

Cell &Cell::operator=(Cell &&cell) {
    if (this == &cell) {
        return *this;
    }
    type = cell.type;
    squad = cell.squad;
    cell.squad = nullptr;
    cell.type = CellEmpty;
    return *this;
}

AmoralSquad *Cell::removeSquad() {
    AmoralSquad *s = squad;
    type = CellEmpty;
    squad = nullptr;
    return s;
}
