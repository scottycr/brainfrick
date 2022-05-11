#include <string>
#include <sstream>

#include <gtest/gtest.h>

#include "celltable.h"

using namespace std;

using namespace celltable;

TEST(CellTableConstructor, Default) {
    CellTable ct;
    ASSERT_EQ(ct.getSize(), 30000);
}

TEST(CellTableConstructor, CustomSize) {
    CellTable ct(500);
    ASSERT_EQ(ct.getSize(), 500);
}

// Used by all CellTableOperators tests.
CellTable ct;

TEST(CellTableOperators, Add) {
    ct.add();
    ASSERT_EQ(ct.getCell(0), 1);
}

TEST(CellTableOperators, Minus) {
    ct.minus();
    ASSERT_EQ(ct.getCell(0), 0);
}

TEST(CellTableOperators, MovePtrRight) {
    char *cellPtr = ct.getCellPtr(1);
    ct.movePtrRight();
    ASSERT_EQ(ct.getPtr(), cellPtr);
}

TEST(CellTableOperators, MovePtrLeft) {
    char *cellPtr = ct.getCellPtr(0);
    ct.movePtrLeft();
    ASSERT_EQ(ct.getPtr(), cellPtr);
}

stringstream ss;
TEST(CellTableOperators, Input) {
    ss << 'H';
    ct.input(ss);
    ASSERT_EQ(*ct.getPtr(), 'H');
}

TEST(CellTableOperators, Print) {
    ss.clear();
    ct.print(ss);
    ASSERT_EQ(ss.str()[0], 'H');
}

TEST(CellTableOperators, PtrIsNotZero) {
    ASSERT_TRUE(ct.ptrIsNotZero());
    ct.movePtrRight();
    ASSERT_FALSE(ct.ptrIsNotZero());
}
