#include "AmoralSquad.h"

AmoralSquad::AmoralSquad(std::string creatureName, std::string school, int initiative,
             int speed, int damage, int protection, int count, int experience) :
            creatureName(creatureName), school(school), initiative(initiative), speed(speed),
            damage(damage), protection(protection), count(count), experience(experience), firstCount(count) {
    
}

void AmoralSquad::setCreatureName(std::string name) {
    this->creatureName = name;
}

void AmoralSquad::setSchool(std::string school) {
    this->school = school;
}

void AmoralSquad::setInitiative(int initiative) {
    if (initiative < 0) {
        throw std::invalid_argument("initiative < 0");
    }
    this->initiative = initiative;
}

void AmoralSquad::setSpeed(int speed) {
    if (speed < 0) {
        throw std::invalid_argument("speed < 0");
    }
    this->speed = speed;
}

void AmoralSquad::setDamage(int damage) {
    if (damage < 0) {
        throw std::invalid_argument("damage < 0");
    }
    this->damage = damage;
}

void AmoralSquad::setProtection(int protection) {
    if (protection < 0) {
        throw std::invalid_argument("protection < 0");
    }
    this->protection = protection;
}

void AmoralSquad::setCount(int count) {
    if (initiative < 0) {
        throw std::invalid_argument("count < 0");
    }
    this->firstCount = count;
    this->count = count;
}

void AmoralSquad::setExperience(int experience) {
    if (experience < 0) {
        throw std::invalid_argument("experience < 0");
    }
    this->experience = experience;
}

//получение и нанесение урона
void AmoralSquad::makeDamageTo(int damage) {
    protection -= damage;
    if (protection <= 0) {
        if (count > 0)
            count--;
        if (count == 0)
            protection = 0;
        else
            protection = 100;
    }
}

int AmoralSquad::getDamageFrom() const {
    return getDamage();
}
