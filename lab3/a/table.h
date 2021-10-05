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

    Element() : busy(0), key(0) {
        info[0] = '\0';
    }

    std::istream& input(std::istream& in) {
        busy = 1;
        in >> key >> info;
        return in;
    }
};

class Table {
private:
    Element elements[SIZE];
public:
    Table() {};
    Table(int keys[], char infos[][INFO_SIZE], int size);
    void print(std::ostream& out) const;
    Element* find(int key) const;
    void add(const Element& element);
    char* getInfo(int key) const;
    void erase(int key);
    void reorganize();
};

#endif
