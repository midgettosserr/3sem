#ifndef SKILL_H
#define SKILL_H

#include <string>
#include <stdexcept>

//класс умение
class Skill {
public:
    enum SquadType {AmoralType, NormalType, AmoralResurrectedType, NormalResurrectedType};
    struct Creature {
        std::string name;
        int speed;
        int damage;
        int experience;
        SquadType type;
    };
private:
    std::string name;
    Creature creature;  //описатель существа
    int minKnowledge;   //минимальное знание школы для этого существа
    int energy;
    double k;       //коэффициент численности от знания школы
public:
    Skill(std::string name = "", Creature creature = Creature(), int minKnowledge = 0, int energy = 0, double k = 0);

    std::string getName() const {return name;}
    Creature getCreature() const {return creature;}
    int getMinKnowledge() const {return minKnowledge;}
    int getEnergy() const {return energy;}
    double getKoefficient() const {return k;}

    void setName(std::string name);
    void setCreature(Creature creature);
    void setMinKnowledge(int minKnowledge);
    void setEnergy(int energy);
    void setKoefficient(double k);

    bool operator==(std::string name) const {return this->name == name;}
};

#endif
