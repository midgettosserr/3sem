#ifndef NORMAL_RESURRECTED_SQUAD_H
#define NORMAL_RESURRECTED_SQUAD_H

#include "NormalSquad.h"

//нормальный воскрешаемый отряд
class NormalResurrectedSquad: public NormalSquad {
public:
    NormalResurrectedSquad(std::string creatureName = "", const School &school = School(), int initiative = 0, int speed = 0, int damage = 0, int protection = 0, int count = 0, int experience = 0);

    void resurrect(int count);
};

#endif