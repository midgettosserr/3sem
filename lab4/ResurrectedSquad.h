#ifndef RESURRECTED_SQUAD_H
#define RESURRECTED_SQUAD_H

#include "Squad.h"

//вскрешаемый отряд
class ResurrectedSquad: public Squad {
private:
    Squad* squad;
public:
    ResurrectedSquad();