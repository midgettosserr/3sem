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
	Squad();
	Squad(std::string, const School&, int, int, int, int, int, int);

	virtual std::string getCreatureName();
	virtual School getSchool() const;
	virtual int getInitiative() const;
	virtual int getSpeed() const;
	virtual int getDamage() const;
	virtual int getProtection() const;
	virtual int getCount() const;
	virtual int getExperience() const;

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
