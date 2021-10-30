#include "gtest/gtest.h"
#include "table.cpp"
#include <fstream>
#include <cstring>

template <class T>
void outTest(const T& t, char strToCompare[][255], int size) {
    std::ofstream outFile("testfile");
    t.print(outFile);
    outFile.close();
    std::ifstream inFile("testfile");
    char str[255];
    int i = 0;
    while (inFile.getline(str, 255)) {
        ASSERT_LT(i, size);
        ASSERT_STREQ(str, strToCompare[i]);
        i++;
    }
    ASSERT_EQ(i, size);
    inFile.close();
    remove("testFile");
}

template <class T>
void outOpTest(const T& t, char strToCompare[][255], int size) {
    std::ofstream outFile("testfile");
    outFile << t;
    outFile.close();
    std::ifstream inFile("testfile");
    char str[255];
    int i = 0;
    while (inFile.getline(str, 255)) {
        ASSERT_LT(i, size);
        ASSERT_STREQ(str, strToCompare[i]);
        i++;
    }
    ASSERT_EQ(i, size);
    inFile.close();
    remove("testFile");
}

TEST(ElementConstructor, DefaultConstructor) {
    Element el;
    ASSERT_EQ(el.busy, 0);
    ASSERT_EQ(el.key, 0); 
    ASSERT_STREQ(el.info, "");
}

TEST(ElementMethods, InputOutput) {
    std::ofstream file("testfile");
    file << "123 abcd";
    file.close();

    Element el;
    std::ifstream testFile("testfile");
    el.input(testFile);
    testFile.close();
    remove("testfile");
    ASSERT_EQ(el.busy, 1);
    ASSERT_EQ(el.key, 123);
    ASSERT_STREQ(el.info, "abcd");

    char str[][255]{"123 abcd"};
    outTest(el, str, 1);
}

TEST(ElementMethods, Operators) {
    std::ofstream file("testfile");
    file << "123 abcd";
    file.close();

    Element el;
    std::ifstream testFile("testfile");
    testFile >> el;
    testFile.close();
    remove("testfile");
    ASSERT_EQ(el.busy, 1);
    ASSERT_EQ(el.key, 123);
    ASSERT_STREQ(el.info, "abcd");

    char str[][255]{"123 abcd"};
    outOpTest(el, str, 1);
}

TEST(TableConstructor, DefaultConstructor) {
    Table table;
    char str[][255]{""};
    outTest(table, str, 0);
}

TEST(TableConstructor, InitConstructor) {
    int keys[3]{1, 2, 3};
    char infos[3][INFO_SIZE]{"ab", "cd", "ef"};
    Table table(keys, infos, 3);
    char str[][255]{"1 ab", "2 cd", "3 ef"};
    outTest(table, str, 3);
    ASSERT_ANY_THROW(Table(keys, infos, -1));
    ASSERT_ANY_THROW(Table(keys, infos, SIZE+1));
}

TEST(TableMethods, ChangeSearch) {
    const char* strings[] {"ab", "cd", "ef", "123", "456", "789", "qwe", "rty", "98", "10"};
    Table table;
    for (int i = 0; i < SIZE; i++) {
        Element el;
        el.key = i;
        strcpy(el.info, strings[i]);
        table.add(el);
    }
    ASSERT_ANY_THROW(table.add(Element()));
    ASSERT_ANY_THROW(table.getInfo(11));
    ASSERT_EQ(table.find(11), nullptr);
    for (int i = 0; i < SIZE; i++) {
        ASSERT_EQ(table.find(i)->key, i);
        ASSERT_STREQ(table.find(i)->info, strings[i]);
        ASSERT_STREQ(table.getInfo(i), strings[i]);
        ASSERT_EQ(table.find(i)->busy, 1);
    }
    for (int i = 0; i < SIZE; i++) {
        table.erase(i);
        ASSERT_ANY_THROW(table.getInfo(i));
        ASSERT_EQ(table.find(i), nullptr);
    }
}

TEST(TableMethods, Reorganize) {
    int keys[3]{1, 2, 3};
    char infos[3][INFO_SIZE]{"ab", "cd", "ef"};
    Table table(keys, infos, 3);
    table.erase(2);
    table.reorganize();
    Element el;
    el.key = 4;
    strcpy(el.info, "qwerty");
    table.add(el);

    char str[][255]{"1 ab", "3 ef", "4 qwerty"};
    outTest(table, str, 3);
}

TEST(TableMethods, OperatorSum)
{
    const char* strings[] {"ab", "cd", "ef", "123", "456"};
    Table table1;
    for (int i = 0; i < SIZE/2; i++) {
        Element el;
        el.key = i;
        strcpy(el.info, strings[i]);
        table1 += el;
    }
    Table table2;
    for (int i = SIZE/2; i < SIZE; i++) {
        Element el;
        el.key = i;
        strcpy(el.info, strings[i]);
        table2 += el;
    }
    Table sum = table1 + table2;
    char str[][255]{"0 ab", "1 cd", "2 ef", "3 123", "4 456", "5 789"};
    outOpTest(sum, str, 5);
    table1 += Element();
    ASSERT_ANY_THROW(sum = table1 + table2);
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
