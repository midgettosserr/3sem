#ifndef RESURRECTED_SQUAD_H
#define RESURRECTED_SQUAD_H

#include "AmoralSquad.h"

//аморальный воскрешаемый отряд
class AmoralResurrectedSquad: public AmoralSquad {
public:
    AmoralResurrectedSquad(std::string creatureName = "", const School &school = School(), int initiative = 0, int speed = 0, int damage = 0, int protection = 0, int count = 0, int experience = 0, bool amoral = false);

    void resurrect(int count);
};

#endif