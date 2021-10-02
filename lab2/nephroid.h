#include <iostream>
#include <string>

using namespace std;

class nephroid {
  private:
    double r;
  public:
    nephroid() {
        r = 0;
    }
    nephroid(double a) {
        if (a < 0)
            //cout << "Error! Please repeat the input: ";
        r = a;
    }
    void radius(double);
    double get_len() const;
    double get_s() const;
    double get_curvature(double) const;
    double get_radius() const;
    double get_x(double) const;
    double get_y(double) const;
    std::string get_equation() const;
};
