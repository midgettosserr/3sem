#include <iostream>
#include "input.h"

using namespace std;

template <class T>
void getValue(T &a) {
    while (!(cin >> a)) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Error! Repeat input: ";
    }
}

template <>
void getValue<Element>(Element &a) {
    a.input(cin);
    while (!cin.good()) {
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout << "Error! Repeat input: ";
        a.input(cin);
    }
}

Table getTable() {
    int N;
    char infos[SIZE][INFO_SIZE];
    int keys[SIZE];
    cout << "Input number of elements: ";
    do {
        getValue(N);
        if (N < 0 || N > SIZE) {
            cout << "Number must be from 0 to " << SIZE << endl;
        }
    } while (N < 0 || N > SIZE);
    for (int i = 0; i < N; i++) {
        cout << "Input key: ";
        getValue(keys[i]);
        cout << "Input info: ";
        getValue(infos[i]);
    }
    return Table(keys, infos, N);
}

void printMenu() {
    cout << "1 - Add new element" << endl;
    cout << "2 - Make new table from N elements" << endl;
    cout << "3 - Print table" << endl;
    cout << "4 - Find element" << endl;
    cout << "5 - Get info" << endl;
    cout << "6 - Remove element" << endl;
    cout << "7 - Reorganize table" << endl;
    cout << "0 - Exit" << endl;
    cout << "> ";
}

void menu(Table& table, int menu) {
    Element element;
    const Element *ptr;
    int key;
    switch (menu) {
        case 1:
            cout << "Input key and info: ";
            getValue(element);
            try {
                table.add(element);
                cout << "Element added" << endl;
            } catch (TableException ex) {
                cout << ex.what() << endl;
            }
            break;
        case 2:
            try {
                table = getTable();
                cout << "Table created" << endl;
            } catch (TableException ex) {
                cout << ex.what() << endl;
            }
            break;
        case 3:
            table.print(cout);
            break;
        case 4:
            cout << "Input key: ";
            getValue(key);
            ptr = table.find(key);
            if (ptr) {
                cout << "Element found, info: " << ptr->info << endl;
            }
            else {
                cout << "Not found" << endl;
            }
            break;
        case 5:
            cout << "Input key: ";
            getValue(key);
            try {
                cout << "Info: " << table.getInfo(key) << endl;
            } catch (TableException ex) {
                cout << ex.what() << endl;
            }
            break;
        case 6:
            cout << "Input key: ";
            getValue(key);
            table.erase(key);
            cout << "Element removed" << endl;
            break;
        case 7:
            break;
        default:
            break;
    }
}
