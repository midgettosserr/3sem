#include <gtest/gtest.h>
#include "nephroid.cpp"
#include <cmath>
#define _USE_MATH_DEFINES

TEST(NephroidConstructor, DefaultConstructor)
{
    nephroid n;
    ASSERT_EQ(n.get_radius(), 0);
}

TEST(NephroidConstructor, InitConstructors)
{
    nephroid n1(1);
    ASSERT_EQ(n1.get_radius(), 1);
    nephroid n2(n1);
    ASSERT_EQ(n2.get_radius(), 1);
}

TEST(NephroidConstructor, TestException)
{
    ASSERT_ANY_THROW(nephroid(-1));
}

TEST(NephroidMethods, Setters)
{
    nephroid n;
    n.set_radius(5);
    ASSERT_EQ(5, n.get_radius());
    ASSERT_ANY_THROW(n.set_radius(-5));
}

TEST(NephroidMethods, Parameters)
{
    nephroid n;
    ASSERT_EQ(0, n.get_len());
    ASSERT_EQ(0, n.get_area());
    ASSERT_EQ(0, n.get_curvature(1));
    ASSERT_EQ(0, n.get_x(1));
    ASSERT_EQ(0, n.get_y(1));
    char eq[255];
    n.get_equation(eq);
    ASSERT_STREQ("(x^2+y^2-0.00)^3 = 0.00*y^2", eq);

    nephroid n2(1);
    const double err = 0.00001;
    ASSERT_EQ(24, n2.get_len());
    ASSERT_NEAR(12*M_PI, n2.get_area(), err);
    ASSERT_NEAR(fabs(3*sin(1)), n2.get_curvature(1), err);
    ASSERT_NEAR(6*cos(1)-4*pow(cos(1), 3), n2.get_x(1), err);
    ASSERT_NEAR(4*pow(sin(1), 3), n2.get_y(1), err);
    n2.get_equation(eq);
    ASSERT_STREQ("(x^2+y^2-4.00)^3 = 108.00*y^2", eq);
}

int main(int argc, char* argv[]){
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
