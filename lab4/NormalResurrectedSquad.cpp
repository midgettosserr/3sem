#include "NormalResurrectedSquad.h"

NormalResurrectedSquad::NormalResurrectedSquad(std::string creatureName, const School &school, int initiative,
                         int speed, int damage, int protection, int count, int experience) : NormalSquad(creatureName, school, initiative, speed, damage, protection, count, experience) {
    
}

void NormalResurrectedSquad::resurrect(int count) {
    if (rand()%100 < 70) {
        setCount(getCount() + count);
    }
}