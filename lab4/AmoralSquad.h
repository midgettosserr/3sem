#ifndef AMORAL_SQUAD_H
#define AMORAL_SQUAD_H

#include "Squad.h"

class AmoralSquad: public Squad {
public:
	AmoralSquad();
	AmoralSquad(std::string, const School&, int, int, int, int, int, int);

	//получение и нанесение урона
};