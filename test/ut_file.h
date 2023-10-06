#pragma once
#include "../src/node.h"
#include "../src/file.h"


TEST(FileSuite, Ping) {
    ASSERT_TRUE(true);
}

TEST(FileSuite, GetFileName) {
    Node * file = new File("test/hello.txt");
    EXPECT_TRUE(file->name() == "hello.txt");
}