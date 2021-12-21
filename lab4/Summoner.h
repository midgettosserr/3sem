#ifndef SUMMONER_H
#define SUMMONER_H

#include <string>
#include <map>

#include <stdexcept>

class Summoner {
private:
    std::string name;
    int initiative;
    int maxHealth;
    int currentHealth;
    int maxEnergy;
    int currentEnergy;
    double accumKoef;
    int experience;
    std::map<std::string, int> schoolKnowledge;
public:
    Summoner(std::string name = "", int initiative = 0, int maxHealth = 0, int currentHealth = 0, int maxEnergy = 0, int currentEnergy = 0, double accumKoef = 0, int experience = 0, const std::map<std::string, int>& schoolKnowledge = std::map<std::string, int>());
    
    std::string getName() const {return name;}
    int getInitiative() const {return initiative;}
    int getMaxHealth() const {return maxHealth;}
    int getCurrentHealth() const {return currentHealth;}
    int getMaxEnergy() const {return maxEnergy;}
    int getCurrentEnergy() const {return currentEnergy;}
    double getAccumKoef() const {return accumKoef;}
    int getExperience() const {return experience;}
    int getSchoolKnowledge(std::string school) const;
    
    void setName(std::string name);
    void setInitiative(int initiative);
    void setMaxHealth(int maxHealth);
    void setCurrentHealth(int currentHealth);
    void setMaxEnergy(int maxEnergy);
    void setCurrentEnergy(int currentEnergy);
    void setAccumKoef(double accumKoef);
    void setExperience(int experience);
    void setSchoolKnowledge(std::string school, int knowledge);
    
    void accumulateEnergy();
    void gainExperience(int exp);
    void improveSchool(std::string school, int exp);
    void makeDamage(int damage);
    
    void decreaseInitiative() {initiative--;}

    std::map<std::string, int>::iterator begin() {return schoolKnowledge.begin();}
    std::map<std::string, int>::iterator end() {return schoolKnowledge.end();}
    
    size_t size() {return schoolKnowledge.size();}
};

#endif
