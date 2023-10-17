#pragma once 

#include "../src/file.h"

TEST(File, normal) {
    File hello("/Users/user/home/hello.txt");
    ASSERT_EQ("hello.txt", hello.name());
    ASSERT_EQ("/Users/user/home/hello.txt", hello.path());
}