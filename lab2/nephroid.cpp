#include "nephroid.h"
#include <iostream>
#include <math.h>
#include <iomanip>
#define _USE_MATH_DEFINES 

double nephroid::get_len() const {
    return 24 * r;
}

double nephroid::get_s() const {
    return 12 * M_PI * r * r;
}

double nephroid::get_curvature(double t) const {
    return abs (3 * r * sin(t));
}

double nephroid::get_radius() const {
    return r;
}

double nephroid::get_x(double t) const {
    return (6 * r * cos(t) - 4 * r * pow(cos(t), 3));
}

double nephroid::get_y(double t) const {
    return (4 * r * pow(sin(t), 3));
}

std::string nephroid::get_equation() const {
    std::stringstream s;
    double a = 4 * r * r, b = 108 * pow(r,4);
    s << "(x^2++y^2+" << a << ")^3=" << b << "*y^2";
    std::string str;
    s >> str;
    return str;
}

void nephroid::radius(double rad) {
    if (rad < 0)
        cout << "Error! Please repeat the input: ";
    r = rad;
}
