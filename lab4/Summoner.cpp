#include "Summoner.h"

Summoner::Summoner(std::string name, int initiative, int maxHealth, int currentHealth,
                int maxEnergy, int currentEnergy, double accumKoef, int experience,
                const std::map<std::string, int> &schoolKnowledge) :
        name(name), initiative(initiative), maxHealth(maxHealth), currentHealth(currentHealth),
        maxEnergy(maxEnergy), currentEnergy(currentEnergy), accumKoef(accumKoef), experience(experience),
        schoolKnowledge(schoolKnowledge) {
    
}

