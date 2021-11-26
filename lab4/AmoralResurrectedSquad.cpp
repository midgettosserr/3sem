#include "AmoralResurrectedSquad.h"

AmoralResurrectedSquad::AmoralResurrectedSquad(std::string creatureName, const School &school, int initiative,
                         int speed, int damage, int protection, int count, int experience) : AmoralSquad(creatureName, school, initiative, speed, damage, protection, count, experience) {
    
}

void AmoralResurrectedSquad::resurrect(int count) {
    if (rand()%100 < 70) {
        setCount(getCount() + count);
    }
}