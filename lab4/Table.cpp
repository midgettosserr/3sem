#include "Table.h"
#include <algorithm>

void Table::addSchool(std::string school) {
	schools.push_back(School(school));
}

void Table::addSkill(std::string school, const Skill &skill) {
	std::vector<School>::iterator it = std::find(schools.begin(), schools.end(), school);
	if (it != schools.end()) {
		it->addSkill(skill);
	}
	else {
		throw std::out_of_range("no such school");
	}
}

std::string Table::getCreature(std::string school, std::string skill) const {
	std::vector<School>::iterator it = std::find(schools.begin(), schools.end(), school);
	if (it != schools.end()) {
		return it->getCreature(skill);
	}
	else {
		throw std::out_of_range("no such school");
	}
}

void Table::setCreature(std::string school, std::string skill, std::string creature) {
	std::vector<School>::iterator it = std::find(schools.begin(), schools.end(), school);
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
