#include "table.h"
#include <cstring>

Element::Element() : busy(0), key(0) {
    info[0] = '\0';
}

std::istream& Element::input(std::istream& in) {
    busy = 1;
    in >> key >> info;
    return in;
}

std::ostream& Element::print(std::ostream& out) const {
    out << key << " " << info << std::endl;
    return out;
}

std::istream& operator>>(std::istream& in, Element& element) {
    return element.input(in);
}

std::ostream& operator<<(std::ostream& out, const Element& element) {
    return element.print(out);
}

Table::Table(int keys[], char infos[][INFO_SIZE], int size) {
    if (size < 0 || size > SIZE) {
        throw TableException("invalid number of elements");
    }
    for (int i = 0; i < size; i++) {
        elements[i].key = keys[i];
        strcpy(elements[i].info, infos[i]);
        elements[i].busy = 1;
    }
}

std::ostream& Table::print(std::ostream& out) const {
    for (int i = 0; i < SIZE; i++) {
        if (elements[i].busy) {
            out << elements[i];
        }
    }
    return out;
}

const Element* Table::find(int key) const {
    for (int i = 0; i < SIZE; i++) {
        if (elements[i].busy && elements[i].key == key) {
            return &elements[i];
        }
    }
    return nullptr;
}

Table& Table::add(const Element& element) {
    bool added = false;
    for (int i = 0; i < SIZE; i++) {
        if (!elements[i].busy) {
            elements[i] = element;
            elements[i].busy = 1;
            added = true;
            break;
        }
    }
    if (!added) {
        throw TableException("table is full");
    }
    return *this;
}

const char* Table::getInfo(int key) const {
    const Element* element = find(key);
    if (element) {
        return element->info;
    }
    else {
        throw TableException("no such element");
    }
}

Table& Table::erase(int key) {
    for (int i = 0; i < SIZE; i++) {
        if (elements[i].busy && elements[i].key == key) {
            elements[i].busy = 0;
            break;
        }
    }
    return *this;
}

Table& Table::reorganize() {
    for (int i = 0; i < SIZE; i++) {
        if (!elements[i].busy) {
            int j = i + 1;
            while (j < SIZE && !elements[j].busy) {
                j++;
            }
            if (j < SIZE) {
                elements[i] = elements[j];
                elements[j].busy = 0;
            }
            else {
                break;
            }
        }
    }
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Table& table) {
    return table.print(out);
}

Table& Table::operator+=(const Element& element) {
    add(element);
    return *this;
}

Table& Table::operator-=(int key) {
    erase(key);
    return *this;
}

const char* Table::operator[](int key) {
    return getInfo(key);
}

Table operator+(const Table& table1, const Table& table2) {
    Table sum;
    int j = 0;
    for (int i = 0; i < SIZE; i++) {
        if (table1.elements[i].busy) {
            if (j >= SIZE) {
                throw TableException("sum overflow");
            }
            sum.elements[j++] = table1.elements[i];
        }
    }
    for (int i = 0; i < SIZE; i++) {
        if (table2.elements[i].busy) {
            if (j >= SIZE) {
                throw TableException("sum overflow");
            }
            sum.elements[j++] = table2.elements[i];
        }
    }
    return sum;
}
