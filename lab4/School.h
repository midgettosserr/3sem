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

    bool operator==(std::string name) const {return this->name == name;}

	//получение существа по умению
	std::string getCreature(std::string skill) const;
	//изменение существа по умению
	void setCreature(std::string skill, std::string creature);
	//кол-во умений в школе
	size_t size() const {return skills.size();}
};

#endif