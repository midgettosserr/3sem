#include <iostream>
#include "prog1.h"

using namespace std;

namespace Prog1 {

List* makeNode(int row_index, int col_index, double x, List *next) {
    List *node = new List;
    node->row = row_index;
    node->col = col_index;
    node->data = x;
    node->next = next;
    return node;
}

void create_new_node(List **p, int row_index, int col_index, double x) {
    List *temp = *p;
    List *r;
    
    if (temp == nullptr) {
        temp = makeNode(row_index, col_index, x, nullptr);
        *p = temp;
    }
    
    else {
        while (temp->next != nullptr)
            temp = temp->next;
        r = makeNode(row_index, col_index, x, nullptr);
        temp->next = r;
    }
}

/*void printList(List *start) {
    List *ptr = start;
    cout << "row_pos: ";
    while (ptr != nullptr) {
        cout << ptr->row << " ";
        ptr = ptr->next;
    }
    cout << endl;

    cout << "col_pos: ";
    ptr = start;
    while (ptr != nullptr) {
        cout << ptr->col << " ";
        ptr = ptr->next;
    }
    cout << endl;

    cout << "Value:   ";
    ptr = start;
    while (ptr != nullptr) {
        cout << ptr->data << " ";
        ptr = ptr->next;
    }
    cout << endl;
}*/

void printMatrix(List *start, int n, int m) {
    List *ptr = start;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (ptr != nullptr && ptr->row == i && ptr->col == j) {
                cout << ptr->data << " ";
                ptr = ptr->next;
            }
            else {
                cout << "0 ";
            }
        }
        cout << endl;
    }
}

void swap(List *first, List *second) {
    double tmp = first->data;
    first->data = second->data;
    second->data = tmp;
}

void addFirst(List **p, int row_index, int col_index, double x) {
    List *temp = makeNode(row_index, col_index, x, *p);
    *p = temp;
}

void removeNode(List *prev, List **start) {
    List *tmp;
    if (prev != nullptr) {
        tmp = prev->next;
        prev->next = prev->next->next;
    }
    else {
        tmp = *start;
        *start = (*start)->next;
    }
    delete tmp;
}

List* swap(List **start, List *first, List *second, int i, int j, int row) {
    if (first && first->next && second && second->next &&
        (first->next->col != i || first->next->row != row) &&
        (second->next->col != j || second->next->row != row)) {
        return nullptr;
    }

    else if (first == second) {
        if (i == j) { 
            return nullptr;
        }
        else if (first == nullptr) {
            (*start)->col = (*start)->col == i ? j : i;
        }
        else {
            first->next->col = first->next->col == i ? j : i;
        }
    }

    else if (first && first->next && first->next->row != row) {
        double data = second != nullptr ? second->next->data : (*start)->data;
        List *tmp = makeNode(row, i, data, first->next);
        first->next = tmp;
        removeNode(second, start);
        return tmp;
    }
    else if (second && second->next && second->next->row != row) {
        double data = first != nullptr ? first->next->data : (*start)->data;
        List *tmp = makeNode(row, j, data, second->next);
        second->next = tmp;
        removeNode(first, start);
        return tmp;
    }

    else if (first == nullptr) {
        if ((*start)->col == i) {
            if (second->next) {
                swap(*start, second->next);
            }
            else {
                create_new_node(start, row, j, (*start)->data);
                removeNode(nullptr, start);
            }
        }
        else {
            addFirst(start, row, i, second->next->data);
            removeNode(second, start);
        }
    }

    else if (second == nullptr) {
        if ((*start)->col == j) {
            if (first->next) {
                swap(first->next, *start);
            }
            else {
                create_new_node(start, row, i, (*start)->data);
                removeNode(nullptr, start);
            }
        }
        else {
            addFirst(start, row, j, first->next->data);
            removeNode(first, start);
        }
    }

    else if (first->next == nullptr) {
        create_new_node(start, row, i, second->next->data);
        removeNode(second, start);
    }

    else if (second->next == nullptr) {
        create_new_node(start, row, j, first->next->data);
        removeNode(first, start);
    }

    else if (first->next->col == i && second->next->col == j) {
        swap(first->next, second->next);
    }

    else if (first->next->col != i && second->next->col != j) {
        return nullptr;
    }

    else if (first->next->col != i) {
        List *tmp =  makeNode(row, i, second->next->data, first->next);
        first->next = tmp;
        removeNode(second, start);
    }
    else {
        List *tmp = makeNode(row, j, first->next->data, second->next);
        second->next = tmp;
        removeNode(first, start);
    }
    return nullptr;
}

void changeMatrix(List **start, int m) {
    if (*start == nullptr) {
        return;
    }
    int row = 0;
    List *ptr = (*start)->col == 0 ? (*start)->next : (*start);
    List *prev = (*start)->col == 0 ? (*start) : nullptr;
    double prevData = (*start)->col == 0 ? (*start)->data : 0;

    while (ptr != nullptr) {
        int i = -1, j = -1, col = 1;
        List *iptr = nullptr, *jptr = nullptr;
        while (ptr != nullptr && ptr->row == row) {
            if (ptr->col == col || ptr->col == 0) {
                if (ptr->col != 0) {
                    if (ptr->data > prevData && i == -1) {
                        i = col;
                        iptr = prev;
                    }
                    if (ptr->data < prevData) {
                        j = col;
                        jptr = prev;
                    }
                }
                prev = ptr;
                prevData = ptr->data;
                col = ptr->col == 0 ? 1 : col + 1;
                ptr = ptr->next;
            }
            else {
                if (0 > prevData && i == -1) {
                    i = col;
                    iptr = prev;
                }
                if (0 < prevData) {
                    j = col;
                    jptr = prev;
                }
                prevData = 0;
                col = ptr->col;
            }
        }
        prevData = 0;
        if (prev != nullptr && prev->col != m - 1) {
            if (prev->data < 0 && i == -1) {
                i = prev->col + 1;
                iptr = prev;
            }
            if (prev->data > 0) {
                j = prev->col + 1;
                jptr = prev;
            }
        }
        if (i != -1 && j != -1 ) {
            List *tmp = swap(start, iptr, jptr, i, j, row);
            if (tmp) {
                prev = tmp;
            }
        }
        row++;
    }
}

void erase(List **start) {
    while ((*start) != nullptr) {
        List *next = (*start)->next;
        delete *start;
        *start = next;
    }
}
}
