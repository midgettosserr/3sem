#ifndef TABLE_H
/**
 @file
 @brief Заголовочный файл с описанием класса Table
 */
#define TABLE_H

#include <string>
#include "Vector.h"
#include "School.h"

/**
 @brief Класс для работы со списком школ

 Каждый элемент таблицы содержит название школы и список у​мений.
 Для удобства доступа к таблице определен к​ласс-итератор.
 */

class Table {
private:
    /**
     Список школ
     */
    mycontainers::vector<School> schools;
public:
    /**
     @brief Конструктор
     @details Создает пустую таблицу
     */
    Table() {}
    /**
     @brief Добавление школы
     @details Добавляет школу с заданным именем в таблицу
     @param school имя школы
     */
    void addSchool(std::string school);
    /**
     @brief Добаление умения
     @details Добавляет заданное умение в школу с заданным именем
     @param school Имя школы
     @param skill Описатель умения
     @throw std::out_of_range В случае отсутствия заданной школы
     */
    void addSkill(std::string school, const Skill &skill);
    /**
     @brief Получение существа
     @details Возвращает существо, относящееся к заданному умению в заданной школе
     @param school Имя школы
     @param skill Имя умения
     @return Описатель существа
     @throw std::out_of_range В случае отсутствия заданной школы или умения
     */
    Skill::Creature getCreature(std::string school, std::string skill) const;
    /**
     @brief Изменение существа
     @details Изменяет существо, относящееся к заданному умению в заданной школе
     @param school Имя школы
     @param skill Имя умения
     @param creature Описатель существа
     @throw std::out_of_range В случае отсутствия заданной школы или умения
     */
    void setCreature(std::string school, std::string skill, Skill::Creature creature);
    /**
     @brief Получение размера таблицы
     @return Количество школ в таблице
     */
    size_t size() const;
    /**
     @brief Получение размера школы
     @param school Имя школы
     @return Количество существ в школе
     @throw std::out_of_range В случае отсутствия заданной школы
     */
    size_t schoolSize(std::string school) const;
    /**
     @brief Получение указателя на школу с заданным именем
     @param school Имя школы
     @return Указатель на описатель школы
     @throw std::out_of_range В случае отсутствия заданной школы
     */
    School *getSchool(std::string school);
    /**
     @brief Получение указателя на умение с заданным именем
     @param school Имя школы
     @param skill Имя умения
     @return Указатель на описатель умения
     @throw std::out_of_range В случае отсутствия заданной школы или умения
     */
    Skill *getSkill(std::string school, std::string skill);
    /**
     @brief Получение итератора на начало таблицы
     @return Итератор на начало таблицы
     */
    mycontainers::vector<School>::iterator begin() {return schools.begin();}
    /**
     @brief Получение итератора на конец таблицы
     @return Итератор на конец таблицы
     */
    mycontainers::vector<School>::iterator end() {return schools.end();}
};

#endif
