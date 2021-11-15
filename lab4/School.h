#ifndef SCHOOL_H
#define SCHOOL_H

#include <string>
#include <vector>
#include "Skill.h"

class School {
private:
	std::string name;	//название школы
	std::vector<Skill> skills;	//список умений
public:
	School();
	School(std::string name);

	std::string getName() const;
	void setName(std::string name);

	void addSkill(const Skill &skill);
};

#endif