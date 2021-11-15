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
	Summoner();
	Summoner(std::string, int, int, int, int, int, double, int);

	void accumulateEnergy();
	void getExperience();
	void improveSchool(std::string school);
	void makeDamage(int damage);
};

#endif