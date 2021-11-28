#include "NormalSquad.h"

NormalSquad::NormalSquad(std::string creatureName, const School &school, int initiative, int speed,
				int damage, int protection, int count, int experience):
				AmoralSquad(creatureName, school, initiative, speed, damage, protection, count,
				experience), moral(0) {

}

void NormalSquad::balanceMoral() {
	if (moral > 0) {
		moral--;
	}
	else if (moral < 0) {
		moral++;
	}
}

void NormalSquad::makeDamageTo(int damage) {
	protection -= damage;
	if (protection <= 0) {
		if (count > 0) {
			count--;
			moral--;
		}
		if (count == 0)
			protection = 0;
		else
			protection = 100;
	}
}

int NormalSquad::getDamageFrom() const {
	return getDamage();
}

int NormalSquad::getInitiative() const {
	return initiative + (double)moral/100. * initiative;
}

int NormalSquad::getSpeed() const {
	return speed + (double)moral/100. * speed;
}

int NormalSquad::getDamage() const {
	return damage + (double)moral/100. * damage;
}

int NormalSquad::getExperience() const {
	return experiecne + (double)moral/100. * experience;
}
