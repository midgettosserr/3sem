#ifndef NORMAL_RESURRECTED_SQUAD_H
#define NORMAL_RESURRECTED_SQUAD_H

#include "NormalSquad.h"
#include "AmoralResurrectedSquad.h"

class NormalResurrectedSquad: public NormalSquad, public AmoralResurrectedSquad {
public:
    NormalResurrectedSquad(std::string creatureName = "", std::string school = "", int initiative = 0, int speed = 0, int damage = 0, int protection = 0, int count = 0, int experience = 0) :
    NormalSquad(), AmoralResurrectedSquad(), AmoralSquad(creatureName, school, initiative, speed, damage, protection, count, experience) {}
    
    //тип для сохранения в файл
    virtual Skill::SquadType type() {return Skill::NormalResurrectedType;}
};

#endif
