#ifndef AMORAL_SQUAD_H
#define AMORAL_SQUAD_H

#include <string>
#include "School.h"
#include "Summoner.h"

//Базовый класс - аморальный отряд
class AmoralSquad {
protected:
    Summoner *summoner;
	std::string creatureName;
	School school;
	int initiative;
	int speed;
	int damage;	//урон
	int protection;	//защита
	int count;
    int firstCount;
	int experience;	//опыт за уничтожение отряда
public:
    AmoralSquad(std::string creatureName = "", const School& school = School(), int initiative = 0, int speed = 0, int damage = 0, int protection = 0, int count = 0, int experience = 0);
    virtual ~AmoralSquad() {}
 
    std::string getCreatureName() const {return creatureName;}
    School &getSchool() {return school;}
    virtual int getInitiative() const {return initiative;}
    virtual int getSpeed() const {return speed;}
    virtual int getDamage() const {return damage;}
    int getProtection() const {return protection;}
    int getCount() const {return count;}
    virtual int getExperience() const {return experience;}
 
    void setCreatureName(std::string name);
    void setSchool(const School &school);
    void setInitiative(int initiative);
    void setSpeed(int speed);
    void setDamage(int damage);
    void setProtection(int protection);
    void setCount(int count);
    void setExperience(int experience);
    
	//получение и нанесение урона
	virtual void makeDamageTo(int damage);
	virtual int getDamageFrom() const;

    Summoner *getSummoner() {return summoner;}
    void setSummoner(Summoner *summoner) {this->summoner = summoner;}

    void decreaseInitiative() {initiative--;}
};

#endif