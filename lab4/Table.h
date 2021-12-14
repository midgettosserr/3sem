#ifndef TABLE_H
#define TABLE_H

#include <string>
#include "Vector.h"
#include "School.h"

class Table {
private:
	mycontainers::vector<School> schools;
public:
	Table() {}

	void addSchool(std::string school);
	void addSkill(std::string school, const Skill &skill);

	std::string getCreature(std::string school, std::string skill) const;	//получить существо по умению
	void setCreature(std::string school, std::string skill, std::string creature);	//изменить существо

	size_t size() const;
	size_t schoolSize(std::string school) const;

	School *getSchool(std::string school);
	Skill *getSkill(std::string school, std::string skill);
    
    class iterator {
    private:
        mycontainers::vector<School>::iterator it;
        iterator(mycontainers::vector<School>::iterator it) : it(it) {}
    public:
        iterator() : it() {}
        iterator(const iterator &it) : it(it.it) {};
        iterator &operator=(const iterator &it) { this->it = it.it; return *this;}
        
        iterator &operator++() {it++; return *this;}
        iterator operator++(int) {iterator iter = *this; it++; return iter;}
        iterator &operator--() {it--; return *this;}
        iterator operator--(int) {iterator iter = *this; it--; return iter;}
        
        School &operator*() const { return it.operator*(); }
        School *operator->() const { return it.operator->(); }
        
        bool operator==(iterator other) const {return it == other.it;}
        bool operator!=(iterator other) const {return it != other.it;}
        
        friend class Table;
    };
    
    iterator begin() {return iterator(schools.begin());}
    iterator end() {return iterator(schools.end());}
};

#endif