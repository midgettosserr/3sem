#include "nephroid.h"
#include <iostream>

using namespace std;

void Menu() {
    cout <<
        "1 - Print the length of the nephroid\n"
        "2 - Print the radius of nephroid\n"
        "3 - Print area\n"
        "4 - Print the x and y values\n"
        "5 - Print the equation of the nephroid\n"
        "6 - Print the radius of nephroid\n"
        //"7 - Change the radius\n"
        "8 - Exit\n";
}

int main() {
    int c = 1;
    cout << "Create nephroid\n";
    nephroid n;
    double rad;

    cout << "Enter the radius: ";
    cin >> rad;
    n.radius(rad);

    Menu();
    while (c != 8) {
        cout << "Enter the menu selection item: ";
        cin >> c;
        switch (c) {
        case 1: {
            double l = n.get_len();
            cout << "The the length of the curve: " << l << "\n";
            break;
        }
        case 2: {
            cout << "Enter the value of the parameter t: ";
            double t;
            cin >> t;
            double r = n.get_curvature(t);
            cout << "The radius of curvature: " << r << "\n";
            break;
        }
        case 3: {
            double s = n.get_s();
            cout << "Area: " << s << "\n";
            break;
        }
        case 4: {
            cout << "Enter the value of the parameter t: ";
            double t;
            cin >> t;
            double x = n.get_x(t);
            double y = n.get_y(t);
            cout << "X value: " << x << "\n";
            cout << "Y value: " << y << "\n";
            break;
        }
        case 5: {
            string str = n.get_equation();
            cout << str << "\n";
            break;
        }
        case 6: {
            double f = n.get_radius();
            cout << "Radius: " << f << "\n";
            break;
        }
        case 7: {
        }
        }
    }
}
