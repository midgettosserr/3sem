#ifndef TABLE_H
#define TABLE_H

#include <string>
#include <vector>
#include "School.h"

class Table {
private:
	std::vector<School> schools;
public:
	Table();

	void addSchool(std::string school);
	void addSkill(std::string school, const Sckill &skill);

	std::string getCreature(std::string school, std::string skill) const;	//получить существо по умению
	void setCreature(std::string school, std::string skill, std::string creature);	//изменить существо

	int size() const;
	int schoolSize(std::string school) const;
};

#endif