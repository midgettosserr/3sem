#ifndef NORMAL_SQUAD_H
#define NORMAL_SQUAD_H

#include "Squad.h"

class NormalSquad: public Squad {
private:
	int moral;
public:
	NormalSquad();
	NormalSquad(std::string, const School&, int, int, int, int, int, int, int);

	void increaseMoral(int moral);
	void balanceMoral();

	//нанести некоторый урон отряду с уменьшением морали
	
	//получить урон, наносимый отрядом
};