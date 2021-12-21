#ifndef AMORAL_RESURRECTED_SQUAD_H
#define AMORAL_RESURRECTED_SQUAD_H

#include "AmoralSquad.h"

class AmoralResurrectedSquad: public virtual AmoralSquad {
public:
    AmoralResurrectedSquad(std::string creatureName = "", std::string school = "", int initiative = 0, int speed = 0, int damage = 0, int protection = 0, int count = 0, int experience = 0) :
    AmoralSquad(creatureName, school, initiative, speed, damage, protection, count, experience) {}

    void resurrect() {
        if (rand()%100 < 70) { 
            setCount(firstCount);
        }
    }
    virtual Skill::SquadType type() override {return Skill::AmoralResurrectedType;}
};

#endif
