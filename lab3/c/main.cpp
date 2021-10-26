#include "table.h"
#include "input.h"

using namespace std;

int main() {
    Table table;
    int m;
    do {
        printMenu();
        getValue(m);
        menu(table, m);
    } while (m);
    return 0;
}
