#ifndef TABLE_H
#define TABLE_H

#include <string>
#include "Vector.h"
#include "School.h"

#include <stdexcept>

class Table {
private:
    mycontainers::vector<School> schools;
public:
    Table() {}
    void addSchool(std::string school);
    void addSkill(std::string school, const Skill &skill);
    Skill::Creature getCreature(std::string school, std::string skill) const;
    void setCreature(std::string school, std::string skill, Skill::Creature);
    size_t size() const;
    size_t schoolSize(std::string school) const;
    School *getSchool(std::string school);
    Skill *getSkill(std::string school, std::string skill);
    
    mycontainers::vector<School>::iterator begin() {return schools.begin();}
    mycontainers::vector<School>::iterator end() {return schools.end();}
};

#endif
