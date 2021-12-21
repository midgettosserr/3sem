#include "School.h"
#include <algorithm>

void School::addSkill(const Skill &skill) {
    skills.push_back(skill);
}

Skill::Creature School::getCreature(std::string skill) const {
    mycontainers::vector<Skill>::const_iterator it = std::find(skills.cbegin(), skills.cend(), skill);
    if (it != skills.cend()) {
        return it->getCreature();
    }
    else {
        throw std::out_of_range("no such skill");
    }
}

Skill *School::getSkill(std::string skill) {
    mycontainers::vector<Skill>::iterator it = std::find(skills.begin(), skills.end(), skill);
    if (it != skills.end()) {
        return it.operator->();
    }
    else {
        throw std::out_of_range("no such skill");
    }
}

void School::setCreature(std::string skill, Skill::Creature creature) {
    mycontainers::vector<Skill>::iterator it = std::find(skills.begin(), skills.end(), skill);
    if (it != skills.end()) {
        return it->setCreature(creature);
    }
    else {
        throw std::out_of_range("no such skill");
    }
}
