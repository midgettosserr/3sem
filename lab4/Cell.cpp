#include "Cell.h"

Cell::Cell(CellTypes type, AmoralSquad *squad) : type(type), squad(squad) {

}

void Cell::setSquad(AmoralSquad *squad) {
	if (type != CellEmpty) {
		throw std::logic_error("the cell is not empty");
	}
	if (squad = nullptr) {
		throw std::invalid_argument("squad can't be null");
	}
	type = CellSquad;
	this->squad = squad;
}


void Cell::setType(CellTypes type, AmoralSquad *squad) {
	if (type == CellSquad) {
		setSquad(squad);
	}
	this->type = type;
}
