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
    void add(const Element& element);
    const char* getInfo(int key) const;
    void erase(int key);
    void reorganize();
    
    friend std::ostream& operator<<(std::ostream& out, const Table& table);
    Table& operator+=(const Element& element);
    Table& operator-=(int key);
    const char* operator[](int key);
    
    Table(const Table& table);
    Table& operator=(const Table& table);
    ~Table();
};

#endif
