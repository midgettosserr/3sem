#ifndef SCHOOL_H
#define SCHOOL_H

#include <string>
#include "Vector.h"
#include "Skill.h"

#include <stdexcept>

class School {
private:
    std::string name;   //название школы
    mycontainers::vector<Skill> skills; //список умений
public:
    School(std::string name = "") : name(name) {}

    std::string getName() const {return name;}
    void setName(std::string name) {this->name = name;}

    void addSkill(const Skill &skill);
    
    bool operator==(std::string name) const {return this->name == name;}

    Skill::Creature getCreature(std::string skill) const;

    void setCreature(std::string skill, Skill::Creature creature);

    size_t size() const {return skills.size();}
    
    Skill *getSkill(std::string skill);
    
    mycontainers::vector<Skill>::iterator begin() {return skills.begin();}
    mycontainers::vector<Skill>::iterator end() {return skills.end();}
};

#endif
