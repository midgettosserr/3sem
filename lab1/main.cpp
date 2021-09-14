#include <iostream>
#include "prog1.h"

using namespace std;

using namespace Prog1;

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
    
    cout << "Input matrix:" << endl;
    printList(first);
    printMatrix(first, row, col);

    changeMatrix(&first, col);
    
    cout << "Output matrix:" << endl;
    printList(first);
    printMatrix(first, row, col);
    
    erase(&first);
    return 0;
}