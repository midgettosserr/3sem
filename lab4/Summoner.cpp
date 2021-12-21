#include "Summoner.h"

Summoner::Summoner(std::string name, int initiative, int maxHealth, int currentHealth,
                   int maxEnergy, int currentEnergy, double accumKoef, int experience,
                   const std::map<std::string, int>& schoolKnowledge) :
        name(name), initiative(initiative), maxHealth(maxHealth), currentHealth(currentHealth),
        maxEnergy(maxEnergy), currentEnergy(currentEnergy), accumKoef(accumKoef), experience(experience),
        schoolKnowledge(schoolKnowledge) {
    
}

int Summoner::getSchoolKnowledge(std::string school) const {
    return schoolKnowledge.at(school);
}

void Summoner::setName(std::string name) {
    this->name = name;
}

void Summoner::setInitiative(int initiative) {
    if (initiative < 0) {
        throw std::invalid_argument("initiative < 0");
    }
    this->initiative = initiative;
}

void Summoner::setMaxHealth(int maxHealth) {
    if (maxHealth < 0) {
        throw std::invalid_argument("max health < 0");
    }
    this->maxHealth = maxHealth;
}

void Summoner::setCurrentHealth(int currentHealth) {
    if (currentHealth < 0) {
        throw std::invalid_argument("current health < 0");
    }
    this->currentHealth = currentHealth;
}

void Summoner::setMaxEnergy(int maxEnergy) {
    if (maxEnergy < 0) {
        throw std::invalid_argument("max energy < 0");
    }
    this->maxEnergy = maxEnergy;
}

void Summoner::setCurrentEnergy(int currentEnergy) {
    if (currentEnergy < 0) {
        throw std::invalid_argument("current energy < 0");
    }
    this->currentEnergy = currentEnergy;
}

void Summoner::setAccumKoef(double accumKoef) {
    if (accumKoef < 0 || accumKoef > 1) {
        throw std::invalid_argument("koef < 0 or koef > 1");
    }
    this->accumKoef = accumKoef;
}

void Summoner::setExperience(int experience) {
    if (experience < 0) {
        throw std::invalid_argument("experience < 0");
    }
    this->experience = experience;
}

void Summoner::setSchoolKnowledge(std::string school, int knowledge) {
    schoolKnowledge[school] = knowledge;
}

void Summoner::accumulateEnergy() {
    currentEnergy += currentEnergy * accumKoef;
    if (currentEnergy > maxEnergy) {
        currentEnergy = maxEnergy;
    }
}

void Summoner::gainExperience(int exp) {
    experience += exp;
}

void Summoner::improveSchool(std::string school, int exp) {
    if (exp <= experience && exp > 0) {
        if (schoolKnowledge.find(school) != schoolKnowledge.end()) {
            schoolKnowledge[school] += exp;
        }
        else {
            schoolKnowledge[school] = exp;
        }
        experience -= exp;
    }
    else {
        throw std::out_of_range("can't spend " + std::to_string(exp) + " experience");
    }
}

void Summoner::makeDamage(int damage) {
    currentHealth -= damage;
    if (currentHealth < 0) {
        currentHealth = 0;
    }
}
