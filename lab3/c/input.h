#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include "table.h"

template <class T>
void getValue(T &a);

Table getTable();

void printMenu();
void menu(Table&, int);

char* getString(std::istream& in);

#endif
