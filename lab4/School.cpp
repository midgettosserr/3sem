#include "School.h"
#include <algorithm>

#include <stdexcept>

void School::addSkill(const Skill &skill) {
	skills.push_back(skill);
}

std::string School::getCreature(std::string skill) const {
	std::vector<Skill>::const_iterator it = std::find(skills.begin(), skills.end(), skill);
	if (it != skills.end()) {
		return it->getCreature();
	}
	else {
		throw std::out_of_range("no such skill");
	}
}

void School::setCreature(std::string skill, std::string creature) {
	std::vector<Skill>::iterator it = std::find(skills.begin(), skills.end(), skill);
	if (it != skills.end()) {
		return it->setCreature(creature);
	}
	else {
		throw std::out_of_range("no such skill");
	}
}


