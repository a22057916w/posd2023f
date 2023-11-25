#pragma once
#include "../src/node.h"
#include "../src/file.h"

#include <string>

TEST(FileSuite, Ping) {
    ASSERT_TRUE(true);
}

TEST(FileSuite, GetFileName) {
    Node * file = new File("test/hello.txt");
    EXPECT_TRUE(file->name() == "hello.txt");
    delete file;
}

TEST(FileSuite, GetFilePath) {
    Node * file = new File("test/hello.txt");
    EXPECT_TRUE(file->path() == "test/hello.txt");
    delete file;
}

TEST(FileSuite, GetDirectoryPath) {
    Node * file  = new File("test/dir/hello.txt");
    EXPECT_EQ(file->directory(), "test/dir");
    delete file;
}

TEST(FileSuite, InvalidAdd) {
    Node * file  = new File("test/dir/hello.txt");
    Node * child = new File("child.txt");

    testing::internal::CaptureStdout();
    file->add(child);
    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "You can only add a node under a directory.\n");
    
    delete file;
    delete child;
}