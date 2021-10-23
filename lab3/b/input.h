#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include "table.h"

#include <stdexcept>
#include <limits>

template <class T>
void getValue(T &a);

Table getTable();

void printMenu();
void menu(Table&, int);
