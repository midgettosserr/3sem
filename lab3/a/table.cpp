#include "table.h"
#include <cstring>

Table::Table(int keys[], char infos[][INFO_SIZE], int size) {
    for (int i = 0; i < size && i < SIZE; i++) {
        elements[i].key = keys[i];
        strcpy(elements[i].info, infos[i]);
        elements[i].busy = 1;
    }
}

void Table::print(std::ostream& out) const {
    for (int i = 0; i < SIZE; i++) {
        if (elements[i].busy) {
            out << elements[i].key << " " << elements[i].info << std::endl;
        }
    }
}

Element* Table::find(int key) const {
    return nullptr;
}

void Table::add(const Element& element) {
}

char* Table::getInfo(int key) const {
    return nullptr;
}

void Table::erase(int key) {  
}

void Table::reorganize() { 
}
