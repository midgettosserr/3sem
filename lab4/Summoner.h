#ifndef SUMMONER_H
#define SUMMONER_H

#include <string>

//класс призыватель
class Summoner {
private:
	std::string name;
	int initiative;
	int maxHealth;
	int currentHealth;
	int maxEnergy;
	int currentEnergy;
	double accumKoef;	//коэффициент аккумуляции
	int experience;
	//значение владения каждой школой
public:
	Summoner(std::string name = "", int initiative = 0, int maxHealth = 0, int currentHealth = 0, int maxEnergy = 0, int currentEnergy = 0, double accumKoef = 0, int experience = 0);

	std::string getName() const {return name;}
	int getInitiative() const {return initiative;}
	int getMaxHealth() const {return maxHealth;}
	int getCurrentHealth() const {return currentHealth;}
	int getMaxEnergy() const {return maxEnergy;}
	int getCurrentEnergy() const {return currentEnergy;}
	int getAccumKoef() const {return accumKoef;}
	int getExperience() const {return experience;}

	void setName(std::string name);
	void setInitiative(int initiative);
	void setMaxHealth(int maxHealth);
	void setCurrentHealth(int currentHealth);
	void setMaxEnergy(int maxEnergy);
	void setCurrentEnergy(int currentEnergy);
	void setAccumKoef(double accumKoef);
	void setExperience(int experience);

	void accumulateEnergy();
	void getExperience();
	void improveSchool(std::string school);
	void makeDamage(int damage);
};

#endif