#include "ResurrectedSquad.h"
#include "AmoralSquad.h"
#include "NormalSquad.h"

ResurrectedSquad::ResurrectedSquad(std::string creatureName, const School &school, int initiative,
           int speed, int damage, int protection, int count, int experience,
           bool amoral) {
    if (amoral) {
        squad = new AmoralSquad(creatureName, school, initiative, speed, damage, protection, count, experience);
    }
    else {
        squad = new NormalSquad(creatureName, school, initiative, speed, damage, protection, count, experience);
    }
}

void ResurrectedSquad::resurrect(int count) {
	if (rand()%100 < 70) {
		squad->setCount(squad->getCount() + count);
	}
}