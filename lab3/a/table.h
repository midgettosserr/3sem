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
};

#endif
