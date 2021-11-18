#ifndef AMORAL_SQUAD_H
#define AMORAL_SQUAD_H

#include "Squad.h"

class AmoralSquad: public Squad {
public:
	AmoralSquad();
	AmoralSquad(std::string creatureName = "", const School& = School(), int initiative = 0, int speed = 0, int damage = 0, int protection = 0, int count = 0, int experience = 0);

	//получение и нанесение урона
	virtual void makeDamageTo(int damage) override;
	virtual void getDamageFrom() const override;
};