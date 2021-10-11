#include "nephroid.h"
#include <iostream>
#include <cmath>
#include <cstring>
#define _USE_MATH_DEFINES

nephroid::nephroid() {
    r = 0;
}

nephroid::nephroid(double a) {
    if (a < 0)
        throw invalid_argument("a < 0");
    r = a;
}

/*nephroid::nephroid(const nephroid& neph) {
    r = neph.r;
}*/

void nephroid::set_radius(double a) {
    if (a < 0)
        throw invalid_argument("a < 0");
    r = a;
}

double nephroid::get_radius() const {
    return r;
}

double nephroid::get_len() const {
    return 24 * r;
}

double nephroid::get_area() const {
    return 12 * M_PI * r * r;
}

double nephroid::get_curvature(double t) const {
    return fabs (3 * r * sin(t));
}

double nephroid::get_x(double t) const {
    return (6 * r * cos(t) - 4 * r * pow(cos(t), 3));
}

double nephroid::get_y(double t) const {
    return (4 * r * pow(sin(t), 3));
}

void nephroid::get_equation(char str[]) const {
    sprintf(str, "(x^2+y^2-%.2f)^3 = %.2f*y^2", 4*r*r, 108 * pow(r, 4));
}
