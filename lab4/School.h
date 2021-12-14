#ifndef SCHOOL_H
#define SCHOOL_H

#include <string>
#include "Vector.h"
#include "Skill.h"

class School {
private:
	std::string name;	//название школы
	mycontainers::vector<Skill> skills;	//список умений
public:;
	School(std::string name = "") : name(name) {}

	std::string getName() const {return name;}
	void setName(std::string name) {this->name = name;}

	void addSkill(const Skill &skill);

    bool operator==(std::string name) const {return this->name == name;}

	std::string getCreature(std::string skill) const;

	void setCreature(std::string skill, std::string creature);

	size_t size() const {return skills.size();}

	Skill *getSkill(std::string skill);
    
	class iterator {
	private:
		mycontainers::vector<Skill>::iterator it;
		iterator(mycontainers::vector<Skill>::iterator it) : it(it) {}
	public:
		iterator() : it() {}
		iterator(const iterator &it) : it(it.it) {};
		iterator &operator=(const iterator &it) { this->it = it.it; return *this;}
        
		iterator &operator++() {it++; return *this;}
		iterator operator++(int) {iterator iter = *this; it++; return iter;}
		iterator &operator--() {it--; return *this;}
		iterator operator--(int) {iterator iter = *this; it--; return iter;}
        
		Skill &operator*() const { return it.operator*(); }
		Skill *operator->() const { return it.operator->(); }
        
		bool operator==(iterator other) const {return it == other.it;}
		bool operator!=(iterator other) const {return it != other.it;}
        
		friend class School;
    };
    
	iterator begin() {return iterator(skills.begin());}
	iterator end() {return iterator(skills.end());}

};

#endif