#ifndef NORMAL_SQUAD_H
#define NORMAL_SQUAD_H

#include "Squad.h"

class NormalSquad: public Squad {
private:
	int moral;
public:
	NormalSquad(std::string creatureName = "", const School& = School(), int initiative = 0, int speed = 0, int damage = 0, int protection = 0, int count = 0, int experience = 0);

	void increaseMoral(int moral) {this->moral += moral;}
	void balanceMoral();

	//нанести некоторый урон отряду с уменьшением морали
	virtual void makeDamageTo(int damage) override;
	//получить урон, наносимый отрядом
	virtual int getDamageFrom() const override;

	virtual int getInitiative() const override;
	virtual int getSpeed() const override;
	virtual int getDamage() const override;
	virtual int getExperience() const override;
};