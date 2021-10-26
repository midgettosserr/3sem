#include "table.h"
#include "input.h"
#include <cstring>

Element::Element() : busy(0), key(0) {
    info = new char[1];
    info[0] = '\0';
}

Element::Element(int busy, int key, const char* info) {
    this->busy = busy;
    this->key = key; 
    this->info = new char[strlen(info) + 1];
    strcpy(this->info, info);
}

std::istream& Element::input(std::istream& in) {
    delete [] info;
    busy = 1;
    in >> key;
    if (in.good()) {
        in.ignore();
        info = getString(in);
    }
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

Element::Element(const Element& element) {
    long len = strlen(element.info);
    info = new char[len+1];
    strcpy(info, element.info);
    busy = element.busy;
    key = element.key;
}

Element& Element::operator=(const Element& element) {
    if (this == &element) {
        return *this;
    }
    delete [] info;
    long len = strlen(element.info);
    info = new char[len+1];
    strcpy(info, element.info);
    busy = element.busy;
    key = element.key;
    return *this;
}

Element::~Element() {
    delete [] info;
}

Table::Table() {
    size = 0;
    elements = nullptr;
}

Table::Table(int *keys, char **infos, int size) {
    if (size < 0) {
        throw TableException("invalid number of elements");
    }
    this->size = size;
    elements = new Element[size];
    for (int i = 0; i < size; i++) {
        elements[i] = Element(1, keys[i], infos[i]);
    }
}

std::ostream& Table::print(std::ostream& out) const {
    for (int i = 0; i < size; i++) {
        if (elements[i].busy) {
            out << elements[i];
        }
    }
    return out;
}

const Element* Table::find(int key) const {
    for (int i = 0; i < size; i++) {
        if (elements[i].busy && elements[i].key == key) {
            return &elements[i];
        }
    }
    return nullptr;
}

void Table::add(const Element& element) {
    bool added = false;
    for (int i = 0; i < size; i++) {
        if (!elements[i].busy) {
            elements[i] = element;
            elements[i].busy = 1;
            added = true;
            break;
        }
    }
    if (!added) {
        Element *tmp = new Element[size + 1];
        for (int i = 0; i < size; i++) {
            tmp[i] = elements[i];
        }
        delete [] elements;
        elements = tmp;
        elements[size++] = element;
    }
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

void Table::erase(int key) {
    for (int i = 0; i < size; i++) {
        if (elements[i].busy && elements[i].key == key) {
            elements[i] = Element();
            break;
        }
    }
}

void Table::reorganize() {
    int N = 0;
    for (int i = 0; i < size; i++) {
        N += elements[i].busy;
    }
    Element *tmp = new Element[N];
    for (int i = 0, j = 0; i < size; i++) {
        if (elements[i].busy) {
            tmp[j++] = elements[i];
        }
    }
    delete [] elements;
    elements = tmp;
    size = N;
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

Table::Table(const Table& table) {
    size = table.size;
    elements = new Element[size];
    for (int i = 0; i < size; i++) {
        elements[i] = table.elements[i];
    }
}

Table& Table::operator=(const Table& table) {
    if (this == &table) {
        return *this;
    }
    delete [] elements;
    size = table.size;
    elements = new Element[size];
    for (int i = 0; i < size; i++) {
        elements[i] = table.elements[i];
    }
    return *this;
}

Table::~Table() {
    delete [] elements;
}
