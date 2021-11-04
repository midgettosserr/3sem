#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include "tableException.h"

struct Element {
    int busy;
    int key;
    char *info;
    Element();
    Element(int busy, int key, const char* info);
    std::istream& input(std::istream& in);
    std::ostream& print(std::ostream& out) const;
    
    friend std::istream& operator>>(std::istream& in, Element& element);
    friend std::ostream& operator<<(std::ostream& out, const Element& element);
    
    Element(const Element& element);
    Element& operator=(const Element& element);
    Element(Element&& element);
    Element& operator=(Element&& element);
    ~Element();
};

class Table {
private:
    Element *elements;
    size_t size;
public:
    Table();
    Table(int *keys, char **infos, int size);
    std::ostream& print(std::ostream& out) const;
    const Element* find(int key) const;
    Table& add(const Element& element);
    const char* getInfo(int key) const;
    Table& erase(int key);
    Table& reorganize();
    
    friend std::ostream& operator<<(std::ostream& out, const Table& table);
    Table& operator+=(const Element& element);
    Table& operator-=(int key);
    const char* operator[](int key);
    friend Table operator+(const Table& table1, const Table& table2); 
    
    Table(const Table& table);
    Table& operator=(const Table& table);
    Table(Table&& table);
    Table& operator=(Table&& table);
    ~Table();
};

#endif
