#ifndef SKILL_H
#define SKILL_H

#include <string>

//класс умение
class Skill {
private:
	std::string name;
	std::string creature;	//описатель существа(имя)
	int minKnowledge;		//минимальное знание школы для этого существа
	int energy;
	double k;		//коэффициент численности от знания школы
public:
	Skill(std::string name = "", std::string creature = "", int minKnowledge = 0, int energy = 0, double k = 0);

	std::string getName() const {return name;}
	std::string getCreature() const {return creature;}
	int getMinKnowledge() const {return minKnowledge;}
	int getEnergy() const {return energy;}
	double getKoefficient() const {return k;}

	void setName(std::string name);
	void setCreature(std::string creature);
	void setMinKnowledge(int minKnowledge);
	void setEnergy(int energy);
	void setKoefficient(double k);

    bool operator==(std::string name) const {return this->name == name;}

};

#endif