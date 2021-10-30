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

Table getTable() {
    int N;
    cout << "Input number of elements: ";
    do {
        getValue(N);
        if (N < 0) {
            cout << "Number must be >= 0" << endl;
        }
    } while (N < 0);
    char **infos = new char*[N];
    int *keys = new int[N];
    for (int i = 0; i < N; i++) {
        cout << "Input key: ";
        getValue(keys[i]);
        cin.ignore();
        cout << "Input info: ";
        infos[i] = getString(cin);
    }
    Table table(keys, infos, N);
    for (int i = 0; i < N; i++) {
        delete [] infos[i];
    }
    delete [] infos;
    delete [] keys;
    return table;
}

void printMenu() {
    cout << "1 - Add new element" << endl;
    cout << "2 - Make new table from N elements" << endl;
    cout << "3 - Print table" << endl;
    cout << "4 - Find element" << endl;
    cout << "5 - Get info" << endl;
    cout << "6 - Remove element" << endl;
    cout << "7 - Reorganize table" << endl;
    cout << "8 - Find sum table+table" << endl;
    cout << "0 - Exit" << endl;
    cout << "> ";
}

void menu(Table& table, int menu) {
    Element element;
    const Element *ptr;
    int key;
    Table sum;
    switch (menu) {
        case 1:
            cout << "Input key and info: ";
            getValue(element);
            try {
                table += element;
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
            cout << table << endl;
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
                cout << "Info: " << table[key] << endl;
            } catch (TableException ex) {
                cout << ex.what() << endl;
            }
            break;
        case 6:
            cout << "Input key: ";
            getValue(key);
            table -= key;
            cout << "Element removed" << endl;
            break;
        case 7:
            table.reorganize();
            cout << "Table reorganized" << endl;
            break;
        case 8:
            sum = table + table;
            cout << sum << endl;
            break;
        default:
            break;
    }
}

char* getString(std::istream& in) {
    char *res = new char[1];
    res[0] = '\0';
    long size = 1;
    char buffer[80];
    do {
        in.clear();
        in.getline(buffer, 80);
        size += strlen(buffer);
        char *tmp = new char[size];
        strcpy(tmp, res);
        strcat(tmp, buffer);
        delete [] res;
        res = tmp;
    } while (!in.good());
    return res;
}
