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
	Skill();
	Skill(std::string name, std::string creature, int minKnowledge, int energy, double k);

	std::string geName() const;
	std::string getCreature() const;
	int getMinKnowledge() const;
	int getEnergy() const;
	double getKoefficient() const;

	void setName(std::string name);
	void setCreature(std::string creature);
	void setMinKnowledge(int minKnowledge);
	void setEnergy(int energy);
	void setKoefficient(double k);
};

#endif