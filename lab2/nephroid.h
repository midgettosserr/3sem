#include <iostream>

using namespace std;

class nephroid {
  private:
    double r;
  public:
    nephroid();
    nephroid(double a);
    //nephroid(const nephroid&);

    void set_radius(double);
    double get_radius() const;

    double get_len() const;
    double get_area() const;
    double get_curvature(double) const;
    double get_x(double) const;
    double get_y(double) const;
    void get_equation(char[]) const;
};
