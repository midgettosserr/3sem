#include <gtest/gtest.h>
#include "Skill.cpp"
#include "School.cpp"
#include "Table.cpp"
#include "AmoralSquad.cpp"
#include "NormalSquad.cpp"
#include "AmoralResurrectedSquad.h"
#include "NormalResurrectedSquad.h"
#include "Cell.cpp"
#include "Level.cpp"
#include "Summoner.cpp"

TEST(SkillClass, Constructor) {
    Skill skill;
    ASSERT_STREQ(skill.getName().c_str(), "");
    ASSERT_STREQ(skill.getCreature().c_str(), "");
    ASSERT_EQ(skill.getMinKnowledge(), 0);
    ASSERT_EQ(skill.getEnergy(), 0);
    ASSERT_EQ(skill.getKoefficient(), 0);

    Skill skill2("abc", "123", 10, 20, 0.5);

    ASSERT_STREQ(skill2.getName().c_str(), "abc");
    ASSERT_STREQ(skill2.getCreature().c_str(), "123");
    ASSERT_EQ(skill2.getMinKnowledge(), 10);
    ASSERT_EQ(skill2.getEnergy(), 20);
    ASSERT_DOUBLE_EQ(skill2.getKoefficient(), 0.5);
}

TEST(SkillClass, Methods) {
    Skill skill;
    skill.setName("abc");
    skill.setCreature("123");
    skill.setMinKnowledge(10);
    skill.setEnergy(20);
    skill.setKoefficient(0.5);

    ASSERT_STREQ(skill.getName().c_str(), "abc");
    ASSERT_STREQ(skill.getCreature().c_str(), "123");

    ASSERT_EQ(skill.getMinKnowledge(), 10);
    ASSERT_EQ(skill.getEnergy(), 20);
    ASSERT_DOUBLE_EQ(skill.getKoefficient(), 0.5);

    ASSERT_TRUE(skill == "abc");
    ASSERT_FALSE(skill == "abcd");
}

TEST(SchoolClass, Constructor) {
    School school;
    ASSERT_STREQ(school.getName().c_str(), "");
    ASSERT_EQ(school.size(), 0);

    School school2("abc");

    ASSERT_STREQ(school2.getName().c_str(), "abc");
    ASSERT_EQ(school2.size(), 0);
}

TEST(SchoolClass, Methods) {
    School school;
    school.setName("abc");
    ASSERT_STREQ(school.getName().c_str(), "abc");
    school.addSkill(Skill("aaa", "bbb", 10, 20, 0.5));
    ASSERT_STREQ(school.getCreature("aaa").c_str(), "bbb");
    school.setCreature("aaa", "ccc");
    ASSERT_STREQ(school.getCreature("aaa").c_str(), "ccc");
    ASSERT_EQ(school.size(), 1);
    ASSERT_TRUE(school == "abc");
    ASSERT_FALSE(school == "aaa");
    ASSERT_ANY_THROW(school.setCreature("bbb", "bbb"));
    ASSERT_ANY_THROW(school.getCreature("bbb"));
}

TEST(TableClass, Constructor) {
    Table table;
    ASSERT_EQ(table.size(), 0);
}

TEST(TableClass, Methods) {
    Table table;
    ASSERT_ANY_THROW(table.addSkill("abc", Skill("aaa", "bbb", 10, 20, 0.5)));
    ASSERT_ANY_THROW(table.getCreature("abc", "aaa"));
    ASSERT_ANY_THROW(table.setCreature("abc", "aaa", "bbb"));
    ASSERT_ANY_THROW(table.schoolSize("abc"));

    table.addSchool("abc");
    ASSERT_EQ(table.schoolSize("abc"), 0);
    table.addSkill("abc", Skill("aaa", "bbb", 10, 20, 0.5));
    ASSERT_EQ(table.schoolSize("abc"), 1);
    ASSERT_STREQ(table.getCreature("abc", "aaa").c_str(), "bbb");
    table.setCreature("abc", "aaa", "ccc");
    ASSERT_STREQ(table.getCreature("abc", "aaa").c_str(), "ccc");
    ASSERT_EQ(table.size(), 1);
    table.addSchool("bbb");
    ASSERT_EQ(table.size(), 2);
}

TEST(AmoralSquadClass, Constructor) {
    AmoralSquad squad;
    ASSERT_STREQ(squad.getCreatureName().c_str(), "");
    ASSERT_STREQ(squad.getSchool().getName().c_str(), "");
    ASSERT_EQ(squad.getSchool().size(), 0);
    ASSERT_EQ(squad.getInitiative(), 0);
    ASSERT_EQ(squad.getSpeed(), 0);
    ASSERT_EQ(squad.getDamage(), 0);
    ASSERT_EQ(squad.getProtection(), 0);
    ASSERT_EQ(squad.getCount(), 0);
    ASSERT_EQ(squad.getExperience(), 0);

    AmoralSquad squad2("abc", School("aaa"), 1, 2, 3, 4, 5, 6);

    ASSERT_STREQ(squad2.getCreatureName().c_str(), "abc");
    ASSERT_STREQ(squad2.getSchool().getName().c_str(), "aaa");
    ASSERT_EQ(squad2.getSchool().size(), 0);
    ASSERT_EQ(squad2.getInitiative(), 1);
    ASSERT_EQ(squad2.getSpeed(), 2);
    ASSERT_EQ(squad2.getDamage(), 3);
    ASSERT_EQ(squad2.getProtection(), 4);
    ASSERT_EQ(squad2.getCount(), 5);
    ASSERT_EQ(squad2.getExperience(), 6);
}

TEST(AmoralSquadClass, Methods) {
    AmoralSquad squad;
    squad.setCreatureName("abc");
    squad.setSchool(School("aaa"));
    squad.setInitiative(1);
    squad.setSpeed(2);
    squad.setDamage(3);
    squad.setProtection(4);
    squad.setCount(5);
    squad.setExperience(6);

    ASSERT_STREQ(squad.getCreatureName().c_str(), "abc");
    ASSERT_STREQ(squad.getSchool().getName().c_str(), "aaa");

    ASSERT_EQ(squad.getSchool().size(), 0);
    ASSERT_EQ(squad.getInitiative(), 1);
    ASSERT_EQ(squad.getSpeed(), 2);
    ASSERT_EQ(squad.getDamage(), 3);
    ASSERT_EQ(squad.getProtection(), 4);
    ASSERT_EQ(squad.getCount(), 5);
    ASSERT_EQ(squad.getExperience(), 6);
    
    ASSERT_EQ(squad.getDamageFrom(), squad.getDamage());
    squad.makeDamageTo(1);
    ASSERT_EQ(squad.getProtection(), 3);
    squad.makeDamageTo(3);
    ASSERT_EQ(squad.getCount(), 4);
    squad.decreaseInitiative();
    ASSERT_LT(squad.getInitiative(), 1);
}

TEST(NormalSquadClass, Constructor) {
    AmoralSquad *squad = new NormalSquad();
    ASSERT_STREQ(squad->getCreatureName().c_str(), "");
    ASSERT_STREQ(squad->getSchool().getName().c_str(), "");
    ASSERT_EQ(squad->getSchool().size(), 0);
    ASSERT_EQ(squad->getInitiative(), 0);
    ASSERT_EQ(squad->getSpeed(), 0);
    ASSERT_EQ(squad->getDamage(), 0);
    ASSERT_EQ(squad->getProtection(), 0);
    ASSERT_EQ(squad->getCount(), 0);
    ASSERT_EQ(squad->getExperience(), 0);
    delete squad;

    squad = new NormalSquad("abc", School("aaa"), 1, 2, 3, 4, 5, 6);

    ASSERT_STREQ(squad->getCreatureName().c_str(), "abc");
    ASSERT_STREQ(squad->getSchool().getName().c_str(), "aaa");
    ASSERT_EQ(squad->getSchool().size(), 0);
    ASSERT_EQ(squad->getInitiative(), 1);
    ASSERT_EQ(squad->getSpeed(), 2);
    ASSERT_EQ(squad->getDamage(), 3);
    ASSERT_EQ(squad->getProtection(), 4);
    ASSERT_EQ(squad->getCount(), 5);
    ASSERT_EQ(squad->getExperience(), 6);
    delete squad;
}

TEST(NormalSquadClass, Methods) {
    AmoralSquad *squad = new NormalSquad();
    squad->setCreatureName("abc");
    squad->setSchool(School("aaa"));
    squad->setInitiative(10);
    squad->setSpeed(20);
    squad->setDamage(30);
    squad->setProtection(40);
    squad->setCount(50);
    squad->setExperience(60);

    ASSERT_STREQ(squad->getCreatureName().c_str(), "abc");
    ASSERT_STREQ(squad->getSchool().getName().c_str(), "aaa");
    ASSERT_EQ(squad->getSchool().size(), 0);
    ASSERT_EQ(squad->getInitiative(), 10);
    ASSERT_EQ(squad->getSpeed(), 20);
    ASSERT_EQ(squad->getDamage(), 30);
    ASSERT_EQ(squad->getProtection(), 40);
    ASSERT_EQ(squad->getCount(), 50);
    ASSERT_EQ(squad->getExperience(), 60);

    NormalSquad *s = dynamic_cast<NormalSquad*>(squad);
    s->increaseMoral(10);
    ASSERT_GT(squad->getInitiative(), 10);
    ASSERT_GT(squad->getSpeed(), 20);
    ASSERT_GT(squad->getDamage(), 30);
    ASSERT_GT(squad->getExperience(), 60);
    for (int i = 0; i < 100; i++) {
        s->balanceMoral();
    }
    ASSERT_EQ(squad->getInitiative(), 10);
    ASSERT_EQ(squad->getSpeed(), 20);
    ASSERT_EQ(squad->getDamage(), 30);
    ASSERT_EQ(squad->getExperience(), 60);
    
    ASSERT_EQ(squad->getDamageFrom(), squad->getDamage());
    squad->makeDamageTo(1);
    ASSERT_EQ(squad->getProtection(), 39);
    squad->makeDamageTo(39);
    ASSERT_EQ(squad->getCount(), 49);
    squad->decreaseInitiative();
    ASSERT_LT(squad->getInitiative(), 19);
    
    for (int i = 0; i < 10; i++) {
        squad->makeDamageTo(1000);
    }
    ASSERT_LT(squad->getInitiative(), 10);
    ASSERT_LT(squad->getSpeed(), 20);
    ASSERT_LT(squad->getDamage(), 30);
    ASSERT_LT(squad->getExperience(), 60);
    delete squad;
}

TEST(ResurrectedSquadClasses, Constructors) {
    AmoralSquad *squad = new AmoralResurrectedSquad();
    ASSERT_STREQ(squad->getCreatureName().c_str(), "");
    ASSERT_STREQ(squad->getSchool().getName().c_str(), "");
    ASSERT_EQ(squad->getSchool().size(), 0);
    ASSERT_EQ(squad->getInitiative(), 0);
    ASSERT_EQ(squad->getSpeed(), 0);
    ASSERT_EQ(squad->getDamage(), 0);
    ASSERT_EQ(squad->getProtection(), 0);
    ASSERT_EQ(squad->getCount(), 0);
    ASSERT_EQ(squad->getExperience(), 0);
    delete squad;

    squad = new AmoralResurrectedSquad("abc", School("aaa"), 1, 2, 3, 4, 5, 6);
    ASSERT_STREQ(squad->getCreatureName().c_str(), "abc");
    ASSERT_STREQ(squad->getSchool().getName().c_str(), "aaa");
    ASSERT_EQ(squad->getSchool().size(), 0);
    ASSERT_EQ(squad->getInitiative(), 1);
    ASSERT_EQ(squad->getSpeed(), 2);
    ASSERT_EQ(squad->getDamage(), 3);
    ASSERT_EQ(squad->getProtection(), 4);
    ASSERT_EQ(squad->getCount(), 5);
    ASSERT_EQ(squad->getExperience(), 6);
    delete squad;

    squad = new NormalResurrectedSquad();
    ASSERT_STREQ(squad->getCreatureName().c_str(), "");
    ASSERT_STREQ(squad->getSchool().getName().c_str(), "");
    ASSERT_EQ(squad->getSchool().size(), 0);
    ASSERT_EQ(squad->getInitiative(), 0);
    ASSERT_EQ(squad->getSpeed(), 0);
    ASSERT_EQ(squad->getDamage(), 0);
    ASSERT_EQ(squad->getProtection(), 0);
    ASSERT_EQ(squad->getCount(), 0);
    ASSERT_EQ(squad->getExperience(), 0);
    delete squad;

    squad = new NormalResurrectedSquad("abc", School("aaa"), 1, 2, 3, 4, 5, 6);
    ASSERT_STREQ(squad->getCreatureName().c_str(), "abc");
    ASSERT_STREQ(squad->getSchool().getName().c_str(), "aaa");
    ASSERT_EQ(squad->getSchool().size(), 0);
    ASSERT_EQ(squad->getInitiative(), 1);
    ASSERT_EQ(squad->getSpeed(), 2);
    ASSERT_EQ(squad->getDamage(), 3);
    ASSERT_EQ(squad->getProtection(), 4);
    ASSERT_EQ(squad->getCount(), 5);
    ASSERT_EQ(squad->getExperience(), 6);
    delete squad;
}

TEST(ResurrectedSquadClasses, Methods) {
    AmoralSquad *squad = new AmoralResurrectedSquad();
    squad->setCreatureName("abc");
    squad->setSchool(School("aaa"));
    squad->setInitiative(1);
    squad->setSpeed(2);
    squad->setDamage(3);
    squad->setProtection(4);
    squad->setCount(5);
    squad->setExperience(6);

    ASSERT_STREQ(squad->getCreatureName().c_str(), "abc");
    ASSERT_STREQ(squad->getSchool().getName().c_str(), "aaa");
    ASSERT_EQ(squad->getSchool().size(), 0);
    ASSERT_EQ(squad->getInitiative(), 1);
    ASSERT_EQ(squad->getSpeed(), 2);
    ASSERT_EQ(squad->getDamage(), 3);
    ASSERT_EQ(squad->getProtection(), 4);
    ASSERT_EQ(squad->getCount(), 5);
    ASSERT_EQ(squad->getExperience(), 6);
    ASSERT_EQ(squad->getDamageFrom(), squad->getDamage());

    squad->makeDamageTo(1);
    ASSERT_EQ(squad->getProtection(), 3);
    squad->makeDamageTo(3);
    ASSERT_EQ(squad->getCount(), 4);
    AmoralResurrectedSquad *r = dynamic_cast<AmoralResurrectedSquad*>(squad);
    r->resurrect();
    ASSERT_GE(squad->getCount(), 4);
    squad->decreaseInitiative();
    ASSERT_LT(squad->getInitiative(), 1);
    delete squad;
    
    squad = new NormalResurrectedSquad();
    squad->setCreatureName("abc");
    squad->setSchool(School("aaa"));
    squad->setInitiative(10);
    squad->setSpeed(20);
    squad->setDamage(30);
    squad->setProtection(40);
    squad->setCount(50);
    squad->setExperience(60);

    ASSERT_STREQ(squad->getCreatureName().c_str(), "abc");
    ASSERT_STREQ(squad->getSchool().getName().c_str(), "aaa");
    ASSERT_EQ(squad->getSchool().size(), 0);
    ASSERT_EQ(squad->getInitiative(), 10);
    ASSERT_EQ(squad->getSpeed(), 20);
    ASSERT_EQ(squad->getDamage(), 30);
    ASSERT_EQ(squad->getProtection(), 40);
    ASSERT_EQ(squad->getCount(), 50);
    ASSERT_EQ(squad->getExperience(), 60);

    NormalSquad *s = dynamic_cast<NormalSquad*>(squad);
    s->increaseMoral(10);
    ASSERT_GT(squad->getInitiative(), 10);
    ASSERT_GT(squad->getSpeed(), 20);
    ASSERT_GT(squad->getDamage(), 30);
    ASSERT_GT(squad->getExperience(), 60);
    for (int i = 0; i < 100; i++) {
        s->balanceMoral();
    }
    ASSERT_EQ(squad->getInitiative(), 10);
    ASSERT_EQ(squad->getSpeed(), 20);
    ASSERT_EQ(squad->getDamage(), 30);
    ASSERT_EQ(squad->getExperience(), 60);
    
    ASSERT_EQ(squad->getDamageFrom(), squad->getDamage());
    squad->makeDamageTo(1);
    ASSERT_EQ(squad->getProtection(), 39);
    squad->makeDamageTo(39);
    ASSERT_EQ(squad->getCount(), 49);
    squad->decreaseInitiative();
    ASSERT_LT(squad->getInitiative(), 19);
    for (int i = 0; i < 10; i++) {
        squad->makeDamageTo(1000);
    }
    ASSERT_LT(squad->getInitiative(), 10);
    ASSERT_LT(squad->getSpeed(), 20);
    ASSERT_LT(squad->getDamage(), 30);
    ASSERT_LT(squad->getExperience(), 60);
    r = dynamic_cast<AmoralResurrectedSquad*>(squad);
    r->resurrect();
    ASSERT_GE(squad->getCount(), 39);
    delete squad;
}

TEST(CellClass, Constructor) {
    Cell cell;
    ASSERT_EQ(cell.getType(), CellEmpty);
    ASSERT_EQ(cell.getSquad(), nullptr);

    AmoralSquad *squad = new NormalSquad();
    Cell cell2(CellSquad, squad);
    ASSERT_EQ(cell2.getType(), CellSquad);
    ASSERT_EQ(cell2.getSquad(), squad);
    ASSERT_ANY_THROW(Cell cell3(CellWall, squad));
    ASSERT_ANY_THROW(Cell cell3(CellSquad));
    delete squad;
}

TEST(CellClass, Methods) {
    AmoralSquad *squad = new NormalSquad();
    Cell cell;
    cell.setType(CellWall);
    ASSERT_EQ(cell.getType(), CellWall);
    ASSERT_ANY_THROW(cell.setSquad(squad));
    cell.setType(CellEmpty);
    cell.setSquad(squad);
    ASSERT_EQ(cell.getType(), CellSquad);
    ASSERT_EQ(cell.getSquad(), squad);
    delete squad;
}

TEST(LevelClass, Constructor) {
    ASSERT_ANY_THROW(Level level(-1, -1));
    Level level(10, 10);
    ASSERT_EQ(level.getCols(), 10);
    ASSERT_EQ(level.getRows(), 10);
    for (int i = 0; i < level.getRows(); i++) {
        for (int j = 0; j < level.getCols(); j++) {
            ASSERT_EQ(level.getCell(i, j), CellEmpty);
        }
    }
    ASSERT_ANY_THROW(level.getCell(10, 10));
}

TEST(LevelClass, Methods) {
    AmoralSquad *squad = new NormalSquad();
    Level level(10, 10);
    level.setSize(8, 8);
    ASSERT_EQ(level.getCols(), 8);
    ASSERT_EQ(level.getRows(), 8);
    ASSERT_ANY_THROW(level.setCell(CellWall, 9, 9));
    level.setCell(CellWall, 1, 1);
    ASSERT_EQ(level.getCell(1, 1), CellWall);
    ASSERT_ANY_THROW(level.setSquad(1, 1, squad));
    level.setSquad(2, 2, squad);
    ASSERT_EQ(level.getCell(2, 2), CellSquad);
    ASSERT_EQ(level.getSquad(2, 2), squad);
    ASSERT_EQ(level.getSquad(3, 3), nullptr);
    delete squad;
}

TEST(SummonerClass, Constructor) {
    Summoner summoner;
    ASSERT_STREQ(summoner.getName().c_str(), "");
    ASSERT_EQ(summoner.getInitiative(), 0);
    ASSERT_EQ(summoner.getMaxEnergy(), 0);
    ASSERT_EQ(summoner.getMaxHealth(), 0);
    ASSERT_EQ(summoner.getCurrentEnergy(), 0);
    ASSERT_EQ(summoner.getCurrentHealth(), 0);
    ASSERT_EQ(summoner.getAccumKoef(), 0);
    ASSERT_EQ(summoner.getExperience(), 0);
    ASSERT_ANY_THROW(summoner.getSchoolKnowledge(""));
    Summoner summoner2("abc", 1, 2, 3, 4, 5, 0.5, 7);
    ASSERT_STREQ(summoner2.getName().c_str(), "abc");
    ASSERT_EQ(summoner2.getInitiative(), 1);
    ASSERT_EQ(summoner2.getMaxEnergy(), 4);
    ASSERT_EQ(summoner2.getMaxHealth(), 2);
    ASSERT_EQ(summoner2.getCurrentEnergy(), 5);
    ASSERT_EQ(summoner2.getCurrentHealth(), 3);
    ASSERT_DOUBLE_EQ(summoner2.getAccumKoef(), 0.5);
    ASSERT_EQ(summoner2.getExperience(), 7);
    ASSERT_ANY_THROW(summoner2.getSchoolKnowledge(""));
}

TEST(SummonerClass, Methods) {
    Summoner summoner;
    summoner.setName("abc");
    summoner.setInitiative(1);
    summoner.setMaxHealth(2);
    summoner.setCurrentHealth(3);
    summoner.setMaxEnergy(40);
    summoner.setCurrentEnergy(5);
    summoner.setAccumKoef(0.5);
    summoner.setExperience(7);

    ASSERT_STREQ(summoner.getName().c_str(), "abc");
    ASSERT_EQ(summoner.getInitiative(), 1);
    ASSERT_EQ(summoner.getMaxEnergy(), 40);
    ASSERT_EQ(summoner.getMaxHealth(), 2);
    ASSERT_EQ(summoner.getCurrentEnergy(), 5);
    ASSERT_EQ(summoner.getCurrentHealth(), 3);
    ASSERT_DOUBLE_EQ(summoner.getAccumKoef(), 0.5);
    ASSERT_EQ(summoner.getExperience(), 7);
    ASSERT_ANY_THROW(summoner.getSchoolKnowledge("aaa"));
    summoner.setSchoolKnowledge("aaa", 10);
    ASSERT_EQ(summoner.getSchoolKnowledge("aaa"), 10);
    ASSERT_ANY_THROW(summoner.improveSchool("bbb"));
    summoner.improveSchool("aaa");
    ASSERT_GT(summoner.getSchoolKnowledge("aaa"), 10);
    
    summoner.accumulateEnergy();
    ASSERT_EQ(summoner.getCurrentEnergy(), summoner.getMaxEnergy());
    summoner.gainExperience();
    ASSERT_GT(summoner.getExperience(), 7);
    summoner.makeDamage(5);
    ASSERT_EQ(summoner.getCurrentHealth(), 0);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
