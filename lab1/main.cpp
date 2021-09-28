#include <iostream>
#include "prog1.h"

using namespace std;

using namespace Prog1;

List* inputMatRows(int row, int col) {
    List *first = nullptr;
    cout << "Enter matrix:" << endl;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            double val;
            while (getNum(val) != 1) {
                cout << "Error! Enter double value: ";
            }
            if (val != 0) {
                create_new_node(&first, i, j, val);
            }
        }
        cout << endl;
    }
    return first;
}

List* inputMatCoordinates(int rows, int cols) {
    List *first = nullptr;
    cout << "Enter elements:" << endl;
    int col, row;
    do {
        cout << "Row (negative for end): ";
        while (getNum(row) != 1) {
            cout << "Error! Enter integer value: ";
        }
        if (row >= 0) {
            cout << "Col: ";
            while (getNum(col) != 1) {
                cout << "Error! Enter integer value: ";
            }
            if (row >= rows || col < 0 || col >= cols) {
                cout << "Error! Enter valid coordinates" << endl;
            }
            else {
                double val;
                cout << "Value: ";
                while (getNum(val) != 1) {
                    cout << "Error! Enter double value: ";
                }
                if (val != 0) {
                    create_new_node(&first, row, col, val);
                }
            }
        }
    } while (row >= 0);
    return first;
}

int main() {
    int row, col;
    cout << "Enter no of rows of the matrix: ";
    while (getNum(row) != 1) {
        cout << "Error! Enter no of rows of the matrix (integer): ";
    }
    cout << "Enter no of columns of the matrix: ";
    while (getNum(col) != 1) {
        cout << "Error! Enter no of columns of the matrix (integer): ";
    }

    int menu;
    cout << "1 - input by rows, 2 - input with coordinates" << endl;
    while (getNum(menu) != 1 || menu < 1 || menu > 2) {
        cout << "Error! Enter 1 or 2: ";
    }

    List *first;
    if (menu == 1) {
        first = inputMatRows(row, col);
    }
    else {
        first = inputMatCoordinates(row, col);
    }

    cout << "Input matrix:" << endl;
    //printList(first);
    printMatrix(first, row, col);

    changeMatrix(&first, col);
    
    cout << "Output matrix:" << endl;
    //printList(first);
    printMatrix(first, row, col);
    
    erase(&first);
    return 0;
}

