namespace Prog1 {

struct List {
    int row;
    int col;
    double data;
    List *next;
};

template <class T>
int getNum(T &a) {
    std::cin >> a;
    if (!std::cin.good()) {
        return -1;
    }
    return 1;
}

void create_new_node(List **p, int row_index, int col_index, double x);
void printList(List *start);
void printMatrix(List *start, int n, int m);
void swap(List *first, List *second);
void addFirst(List **p, int row_index, int col_index, double x);
void removeNode(List *prev, List **start);
List* swap(List **start, List *first, List *second, int i, int j, int row);
void changeMatrix(List **start, int m);
void erase(List **start);
}
