#include "Skill.h"

Skill::Skill(std::string name, Creature creature, int minKnowledge, int energy, double k) :
        name(name), creature(creature), minKnowledge(minKnowledge), energy(energy), k(k) {
    
}

void Skill::setName(std::string name) {
    this->name = name;
}

void Skill::setCreature(Creature creature) {
    this->creature = creature;
}

void Skill::setMinKnowledge(int minKnowledge) {
    if (minKnowledge < 0) {
        throw std::invalid_argument("min knowledge < 0");
    }
    this->minKnowledge = minKnowledge;
}

void Skill::setEnergy(int energy) {
    if (energy < 0) {
        throw std::invalid_argument("energy < 0");
    }
    this->energy = energy;
}

void Skill::setKoefficient(double k) {
    if (k < 0 || k > 1) {
        throw std::invalid_argument("k < 0 or k > 1");
    }
    this->k = k;
}
