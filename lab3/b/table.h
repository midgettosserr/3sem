#ifndef TABLE_H
#define TABLE_H

#include <iostream>
#include "tableException.h"

const int INFO_SIZE = 255;
const int SIZE = 10;

struct Element {
    int busy;
    int key;
    char info[INFO_SIZE];
    Element();
    std::istream& input(std::istream& in);
    std::ostream& print(std::ostream& out) const;
    
    friend std::istream& operator>>(std::istream& in, Element& element);
    friend std::ostream& operator<<(std::ostream& out, const Element& element);
};

class Table {
private:
    Element elements[SIZE];
public:
    Table() {};
    Table(int keys[], char infos[][INFO_SIZE], int size);
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
    Table operator+(const Table& table) const;
};

#endif
