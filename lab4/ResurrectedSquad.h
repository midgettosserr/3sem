#ifndef RESURRECTED_SQUAD_H
#define RESURRECTED_SQUAD_H

#include "Squad.h"

//воскрешаемый отряд
class ResurrectedSquad: public Squad {
private:
    Squad* squad;
public:
    ResurrectedSquad(std::string creatureName = "", const School &school = School(), int initiative = 0, int speed = 0, int damage = 0, int protection = 0, int count = 0, int experience = 0);
    ~ResurrectedSquad() {delete squad;}

    virtual std::string getCreatureName() const override {return squad->getCreatureName();}
    virtual School &getSchool() override {return squad->getSchool();}
    virtual int getInitiative() const override {return squad->getInitiative();}
    virtual int getSpeed() const override {return squad->getSpeed();}
    virtual int getDamage() const override {return squad->getDamage();}
    virtual int getProtection() const override {return squad->getProtection();}
    virtual int getCount() const override {return squad->getCount();}
    virtual int getExperience() const override {return squad->getExperience();}

    virtual void setCreatureName(std::string name) override {squad->setCreatureName(name);}
    virtual void setSchool(const School &school) override {squad->setSchool(school);}
    virtual void setInitiative(int initiative) override {squad->setInitiative(initiative);}
    virtual void setSpeed(int speed) override {squad->setSpeed(speed);}
    virtual void setDamage(int damage) override {squad->setDamage(damage);}
    virtual void setProtection(int protection) override {squad->setProtection(protection);}
    virtual void setCount(int count) override {squad->setCount(count);}
    virtual void setExperience(int experience) override {squad->setExperience(experience);}

    virtual void makeDamageTo(int damage) override {squad->makeDamageTo(damage);}  //нанести урон
    virtual void getDamageFrom(int damage) const override {squad->getDamageFrom();}   //получить урон, наносимый отрядом

    void resurrect(int count);
};

#endif