#ifndef SCHOOL_H
#define SCHOOL_H

#include <string>
#include <vector>
#include "Skill.h"

class School {
private:
	std::string name;	//название школы
	std::vector<Skill> skills;	//список умений
public:;
	School(std::string name = "") : name(name) {}

	std::string getName() const {return name;}
	void setName(std::string name) {this->name = name;}

	void addSkill(const Skill &skill);
};

#endif