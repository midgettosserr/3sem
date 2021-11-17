#ifndef SQUAD_H
#define SQUAD_H

#include <string>
#include "School.h"		//школа

//базовый класс отряда
class Squad {
protected:
	std::string creatureName;
	School school;
	int initiative;
	int speed;
	int damage;	//урон
	int protection;	//защита
	int count;
	int experience;	//опыт за уничтожение отряда
public:
	Squad(std::string creatureName = "", const School& school = School(), int initiative = 0, int speed = 0, int damage = 0, int protection = 0, int count = 0, int experience = 0);

	virtual std::string getCreatureName() const {return creatureName;}
	virtual School getSchool() const {return school;}
	virtual int getInitiative() const {return initiative;}
	virtual int getSpeed() const {return speed;}
	virtual int getDamage() const {return damage;}
	virtual int getProtection() const {return protection;}
	virtual int getCount() const {return count;}
	virtual int getExperience() const {return experience;}

	virtual void setCreatureName(std::string name);
	virtual void setSchool(const School &school);
	virtual void setInitiative(int initiative);
	virtual void setSpeed(int speed);
	virtual void setDamage(int damage);
	virtual void setProtection(int protection);
	virtual void setCount(int count);
	virtual void setExperience(int experience);

	virtual void makeDamageTo(int damage) const = 0;	//нанести урон
	virtual void getDamageFrom(int damage) const = 0;	//получить урон, наносимый отрядом
};

#endif
