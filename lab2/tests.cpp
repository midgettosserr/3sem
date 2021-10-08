#include "nephroid.cpp"
#include <gtest/gtest.h>

TEST(nephroid, testget_radius){
        nephroid a1;
        ASSERT_EQ(0, a1.get_radius());
        nephroid a2(15);
        ASSERT_EQ(15, a2.get_radius());
        ASSERT_ANY_THROW(nephroid(-78));
}

TEST(nephroid, testset_radius){
        nephroid a(10);
        a.set_radius(17);
        ASSERT_NEAR(a.get_radius(), 17, 0.1);
        a.set_radius(5);
        EXPECT_THROW(a.set_radius(-5), std::exception);
}

TEST(nephroid, testget_len){
        nephroid a(2);
        ASSERT_EQ(48, a.get_len());
        nephroid a1(20);
        ASSERT_EQ(480, a1.get_len());
}

TEST(nephroid, testget_area){
        nephroid a(4);
        ASSERT_NEAR(a.get_area(), 602.88, 0.4);
        nephroid a1(8);
        ASSERT_NE(2411.52, a1.get_area());
}

TEST(nephroid, testget_curvature){
        nephroid a(7);
        ASSERT_NEAR(a.get_curvature(M_PI), 0, 0.1);
}

TEST(nephroid, testget_x){
        nephroid a(11);
        ASSERT_NEAR(a.get_x(M_PI), 0, 23);
}

TEST(nephroid, testget_y){
        nephroid a(11);
        ASSERT_NEAR(a.get_y(M_PI), 0, 0.1);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
