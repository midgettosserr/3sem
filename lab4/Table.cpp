#include "Table.h"
#include <algorithm>

#include <stdexcept>

void Table::addSchool(std::string school) {
    schools.push_back(School(school));
}

void Table::addSkill(std::string school, const Skill& skill) {
    mycontainers::vector<School>::iterator it = std::find(schools.begin(), schools.end(), school);
    if (it != schools.end()) {
        it->addSkill(skill);
    }
    else {
        throw std::out_of_range("no such school");
    }
}

std::string Table::getCreature(std::string school, std::string skill) const {
    mycontainers::vector<School>::const_iterator it = std::find(schools.cbegin(), schools.cend(), school);
    if (it != schools.cend()) {
        return it->getCreature(skill);
    }
    else {
        throw std::out_of_range("no such school");
    }
}

Skill *Table::getSkill(std::string school, std::string skill) {
    mycontainers::vector<School>::iterator it = std::find(schools.begin(), schools.end(), school);
    if (it != schools.end()) {
        return it->getSkill(skill);
    }
    else {
        throw std::out_of_range("no such school");
    }
}

void Table::setCreature(std::string school, std::string skill, std::string creature) {
    mycontainers::vector<School>::iterator it = std::find(schools.begin(), schools.end(), school);
    if (it != schools.end()) {
        return it->setCreature(skill, creature);
    }
    else {
        throw std::out_of_range("no such school");
    }
}

size_t Table::size() const {
    return schools.size();
}

size_t Table::schoolSize(std::string school) const {
    mycontainers::vector<School>::const_iterator it = std::find(schools.cbegin(), schools.cend(), school);
    if (it != schools.cend()) {
        return it->size();
    }
    else {
        throw std::out_of_range("no such school");
    }
}