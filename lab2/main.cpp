#include "nephroid.h"
#include <iostream>

using namespace std;

void printmenu(){
        cout << "1 - Set radius of nephroid" << endl;
        cout << "2 - Get radius of nephroid" << endl;
        cout << "3 - Get arclength" << endl;
        cout << "4 - Get area" << endl;
        cout << "5 - Get radius of curvature" << endl;
        cout << "6 - Get x and y coordinates" << endl;
        cout << "7 - Get the equation of implicit representation" << endl;
        cout << "0 - Quit" << endl;
        cout << "> ";
}

int main() {
    nephroid neph;
    int menu;
    double a, t;
    char str[255];
    do {
        printmenu();
        cin >> menu;
        switch (menu) {
            case 1:
                cout << "Input radius a = ";
                cin >> a;
                try {
                    neph.set_radius(a);
                } catch (invalid_argument ex) {
                    cout << "Error! " << ex.what() << endl;
                }
                break;
            case 2:
                cout << "Radius a = " << neph.get_radius() << endl;
                break;
            case 3:
                cout << "Arclength L = " << neph.get_len() << endl;
                break;
            case 4:
                cout << "Area A = " << neph.get_area() << endl;
                break;
            case 5:
                cout << "Enter t = ";
                cin >> t;
                cout << "Radius of curvature p = " << neph.get_curvature(t) << endl;
                break;
            case 6:
                cout << "Enter t = ";
                cin >> t;
                cout << "Coordinates are (" << neph.get_x(t) << ", " << neph.get_y(t) << ")" << endl;
                break;
            case 7:
                neph.get_equation(str);
                cout << str << endl;
                break;
            case 0:
                break;
            default:
                cout << "Incorrect menu item" << endl;
                break;
        }
    } while (menu != 0);
}
